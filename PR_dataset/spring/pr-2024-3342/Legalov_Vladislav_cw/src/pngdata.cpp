#include "pngdata.hpp"

uint32_t reversebyte(uint32_t x){
    x = (x & 0x00FF00FF) <<  8 | (x & 0xFF00FF00) >>  8;
    x = (x & 0x0000FFFF) << 16 | (x & 0xFFFF0000) >> 16;
    return x;
}

void checkpointer(void *ptr){
	if (ptr == NULL){
		std::cout <<  "Error: not enough memory\n";
		exit(48);
	}
}

dataPNG::Chunck::Chunck(){
    length = 0;
    name = 0;
    crc = 0;
    data = NULL;
}

dataPNG::Chunck::Chunck(uint32_t len, uint32_t str, uint8_t* data){
	length = len;
	name = str;
	if(length){
		this->data = new uint8_t[length];
		checkpointer(this->data);
		memcpy(this->data, data, length);
    }
	crc = calcCRC();
}

int
dataPNG::Chunck::setFromfile(FILE *file){
    fread(&length, 1, 4, file);
    length = reversebyte(length);
    fread(&name, 1, 4, file);
    if(length){
		if (data != NULL)
			delete[] data;
        data = new uint8_t[length];
		checkpointer(data);
        fread(data, 1, length, file);
    }
    fread(&crc, 1, 4, file);
    crc = reversebyte(crc);
    return 0;
}


void
dataPNG::Chunck::writeInFile(FILE *file){
	uint32_t buffer;
	buffer = reversebyte(length);
    fwrite(&buffer, 1, 4, file);
    fwrite(&name, 1, 4, file);
    if(length){
        fwrite(data, 1, length, file);
    }
    buffer = reversebyte(crc);
    fwrite(&buffer, 1, 4, file);
}

uint32_t
dataPNG::Chunck::calcCRC(){
	uint64_t len = length + 4;
	uint8_t *buf = new uint8_t[len];
	checkpointer(buf);
	uint8_t *ptr = buf;
	memcpy(buf, &name,  4);
	if(length)
		memcpy(buf + 4, data,  length);

	uint64_t table[256];
	uint64_t crc;
	for (int i = 0; i < 256; i++)
	{
		crc = i;
		for (int j = 0; j < 8; j++)
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
		table[i] = crc;
	}
	crc = 0xFFFFFFFFUL;
	while (len--)
		crc = table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
	delete[] ptr;
	return crc ^ 0xFFFFFFFFUL;
}

dataPNG::~dataPNG(){
	for (auto &i : chuncks)
		if (i.data){
			delete[] i.data;
			i.data = NULL;
		}
}

int
dataPNG::readPNG(FILE *file){
	Bytef sign[8];
	palette = NULL;
	fread(sign, 1, 8, file);
	if (!memcmp(sign, SINATUREPNG, 8)){
		do{
			chuncks.push_back(Chunck());
			chuncks.back().setFromfile(file);
			if(chuncks.back().name == PLTE){
				palette = chuncks.back().data;
				palettesize = chuncks.back().length;
			}
		}
		while(chuncks.back().name != IEND);
		width = reversebyte(*(uint32_t*)&chuncks[0].data[0]);
		height = reversebyte(*(uint32_t*)&chuncks[0].data[4]);
		depth = *(uint8_t*)&chuncks[0].data[8];
		colortype = *(uint8_t*)&chuncks[0].data[9];
		for(auto &chunck : chuncks){
			if(chunck.crc !=  chunck.calcCRC()){
				std::cout <<  "Error: invalid value CRC\n";
				exit(45);
			}
		}

		if(depth != 8){
			std::cout <<  "Images with bit depth " << depth << " is not supported\n";
			exit(46);
		}
		switch(colortype){
		case 6:
			pixelsize = 4;
			break;
		case 3:
			pixelsize = 1;
			break;
		case 2:
			pixelsize = 3;
			break;
		default:
			std::cout <<  "Color type: " << colortype << " is not supported\n";
			exit(47);
		}
	}
	else{
		std::cout << "File is not recognized as a PNG\n";
        exit(44);
	}
	return 0;
}

void
dataPNG::printdata(){
	printf("Image width: %u\n", width);
	printf("Image height: %u\n", height);
	printf("Image depth: %hhu\n", depth);
    if (colortype == 2){
        printf("Image Colour Type: RGB\n");
    } else if (colortype == 6){
        printf("Image Colour Type: RGBA\n");
    } else {
		printf("Image Colour Type: RGB with palette\n");
	}
}

Image*
dataPNG::decodImage(){
	uint64_t size = sizedata();
	uint8_t *arraybyte;
	uncompressdata(arraybyte, size);
	uint8_t **bitmap = fillimage(arraybyte,  size);
	delete[] arraybyte;
	Image* result = new Image;
	checkpointer(result);
	if(colortype == 3){
		fillFromPalette(bitmap);
		pixelsize = 3;
	}
	result->height = height;
	result->width = width;
	result->pixelsize = pixelsize;
	result->bitmap = bitmap;
	return result;
}

void
dataPNG::fillFromPalette(uint8_t **&bitmap){
	uint8_t **newbitmap = new uint8_t*[height];
	checkpointer((void*)newbitmap);
	for(int i = 0; i < height; ++i){
		newbitmap[i] = new uint8_t[width * 3];
		checkpointer(newbitmap[i]);
	}


	for(int i = 0; i < height; ++i)
		for(int j = 0; j < width; ++j)
			if(bitmap[i][j] < palettesize / 3)
				*(rgb*)&newbitmap[i][j * 3] = *(rgb*)&palette[bitmap[i][j] * 3];

	for(int i = 0; i < height; ++i)
		delete[] bitmap[i];
	delete[] bitmap;
	bitmap = newbitmap;
}

uint64_t
dataPNG::sizedata(){
	uint64_t size = 0;
	for(auto &a : chuncks)
		if(a.name == IDAT)
			size += a.length;
	return size;
}

int
dataPNG::uncompressdata(uint8_t *&array, uint64_t& size){
	uint8_t *buffer = new uint8_t[size];
	checkpointer(buffer);
	uint8_t *ptr = buffer;
	for(auto &a : chuncks)
		if(a.name == IDAT){
			memcpy(ptr,  a.data,  a.length);
			ptr += a.length;
		}
	uint64_t destlen = width * height * pixelsize + height;
	ptr = new uint8_t[destlen];
	checkpointer(ptr);
	uncompress(ptr,  &destlen,  buffer,  size);
	delete[] buffer;
	array = ptr;
	size = destlen;
	return 0;
}

uint8_t**
dataPNG::fillimage(uint8_t* array, uint64_t size){
	uint8_t **array2dim = new uint8_t*[height];
	checkpointer(array2dim);
	uint8_t* buffer;
	uint8_t* filters = new uint8_t[height];
	checkpointer(filters);
	for (uint64_t i = 0; i < height; ++i){
		array2dim[i] = array + i * (width * pixelsize + 1);
		filters[i] = array2dim[i][0];
	}

	for(uint64_t i = 0; i < height; ++i){
		buffer = new uint8_t[width * pixelsize];
		checkpointer(buffer);
		memcpy(buffer, array2dim[i] + 1, width * pixelsize);
		array2dim[i] = buffer;
	}

	for(uint64_t i = 0; i < height; ++i)
		for(uint64_t j = 0; j < width * pixelsize; ++j)
			recon(array2dim, filters[i], j, i);

	delete[] filters;
	return array2dim;
}

void
dataPNG::recon(uint8_t **array,  uint8_t filter, uint64_t x, uint64_t y){
	uint8_t a = 0, b = 0, c = 0;
	if(x >= pixelsize)
		a = array[y][x - pixelsize];
	if(y > 0)
		b = array[y - 1][x];
	if(x >= pixelsize && y > 0)
		c = array[y - 1][x - pixelsize];

	switch(filter){
	case 0:
		break;
	case 1:
		array[y][x] += a;
		break;
	case 2:
		array[y][x] += b;
		break;
	case 3:
		array[y][x] += ((uint16_t)a + (uint16_t)b) / 2;
		break;
	case 4:
		array[y][x] += paethPredictor(a, b, c);
		break;
	}
}

uint8_t
dataPNG::paethPredictor(int a,  int b, int c){
	int p, pa, pb, pc;
	p = a + b - c;
	pa = abs(p - a);
	pb = abs(p - b);
	pc = abs(p - c);
	if (pa <= pb && pa <= pc)
		return a;
	else if (pb <= pc)
		return b;
	else return c;
}

int
dataPNG::writePNG(FILE *file){
	fwrite(SINATUREPNG, 1,  8, file);
	for(auto &chunck : chuncks){
		chunck.writeInFile(file);
	}
	return 0;
}

int
dataPNG::updateData(Image &image){
	width = image.width;
	height = image.height;
	pixelsize = image.pixelsize;
	uint64_t size = width * height * pixelsize + height;
	uint8_t *array = new uint8_t[size];
	checkpointer(array);
	for(uint64_t i = 0; i < height; ++i){
		array[i * (width * pixelsize + 1)] = 0;
		memcpy(array + i * (width * pixelsize + 1) + 1, image.bitmap[i], width * pixelsize);
	}
	compressdata(array, size);
	std::vector<Chunck> uptadechuncks;
	uint32_t n = 0;
	while(chuncks[n].name != IDAT){
		if(chuncks[n].name != PLTE)
			uptadechuncks.push_back(chuncks[n]);
		++n;
	}

	for(uint64_t i = 0; i < (size / IDATSIZE); ++i)
		uptadechuncks.push_back(Chunck(IDATSIZE, IDAT, array + i * IDATSIZE));
	if(size % IDATSIZE)
		uptadechuncks.push_back(Chunck(size % IDATSIZE, IDAT, array + (size / IDATSIZE) * IDATSIZE));

	while(n < chuncks.size()){
		if (chuncks[n].name != IDAT)
			uptadechuncks.push_back(chuncks[n]);
		++n;
	}

	chuncks = uptadechuncks;
	delete[] array;
	*(uint32_t*)&chuncks[0].data[0] = reversebyte(width);
	*(uint32_t*)&chuncks[0].data[4] = reversebyte(height);
	*(uint8_t*)&chuncks[0].data[8] = 8;
	*(uint8_t*)&chuncks[0].data[9] = (pixelsize == 4) ? 6 : 2;
	chuncks[0].crc = chuncks[0].calcCRC();
	return 0;
}

int
dataPNG::compressdata(uint8_t *&array, uint64_t &size){
	uint64_t destlen = compressBound(size);
	uint8_t *dest = new uint8_t[destlen];
	checkpointer(dest);
	compress(dest,  &destlen,  array,  size);
	delete[] array;
	size = destlen;
	array = dest;
	return 0;
}



