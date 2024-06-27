#include"BmpImage.h"
#include"UserInteraction.h"
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdbool>

BmpImage::BmpImage() noexcept
{
    mPixelArr=nullptr;
    mHeight=0;
    mWidth=0;
}

int BmpImage::checkFileFormat() noexcept
{
    if(mBmfh.signature!=SIGNATURE_VALUE)
        return 1;
    if(mBmih.headerSize!=sizeof(BmpInfoHeader))
        return 1;
    if(mBmih.bitsPerPixel!=BITS_PER_PIXEL_VALUE)
        return 1;
    if(mBmih.compression!=COMPRESSION_VALUE)
        return 1;
    return 0;
}

BmpImage::BmpImage(const std::string filePath)
{
    this->open(filePath);
}

void BmpImage::fileHeaderInit() noexcept
{
    this->mBmfh.signature=SIGNATURE_VALUE;
    this->mBmfh.fileSize=mWidth*mHeight*3+sizeof(BmpInfoHeader)+sizeof(BmpFileHeader);
    this->mBmfh.reserved1=0;
    this->mBmfh.reserved2=0;
    this->mBmfh.pixelArrOffset=sizeof(BmpInfoHeader)+sizeof(BmpFileHeader);
}

void BmpImage::infoHeaderInit() noexcept
{
    this->mBmih.headerSize=sizeof(BmpInfoHeader);
    this->mBmih.width=mWidth;
    this->mBmih.height=mHeight;
    this->mBmih.planes=1;
    this->mBmih.bitsPerPixel=BITS_PER_PIXEL_VALUE;
    this->mBmih.compression=COMPRESSION_VALUE;
    this->mBmih.imageSize=mWidth*mHeight*3;
    this->mBmih.xPixelsPerMeter=0;
    this->mBmih.yPixelsPerMeter=0;
    this->mBmih.colorsInColorTable=0;
    this->mBmih.importantColorCount=0;
}

BmpImage::BmpImage(const int width, const int height, Rgb defaultColor)
{
    if (width<=0 || height<=0)
        throw std::invalid_argument("Invalid image size!");
    if (checkColor(defaultColor))
        throw std::invalid_argument("Non-Rgb color type!\n");
    mPixelArr=new Rgb*[height];
    for(int i=0;i<height;i++)
    {
        mPixelArr[i]=new Rgb[width];
        for(int j=0;j<width;j++)
            mPixelArr[i][j]=defaultColor;
    }
    this->mHeight=height;
    this->mWidth=width;
    fileHeaderInit();
    infoHeaderInit();
}

void BmpImage::open(const std::string filePath)
{
    std::FILE *f=fopen(filePath.c_str(), "rb");
    if(f==nullptr)
    {
        throw InvalidImageException("Unable to open bmp file!\n");
    }
    fread(&mBmfh, 1, sizeof(BmpFileHeader), f);
    fread(&mBmih, 1, sizeof(BmpInfoHeader), f);
    if(checkFileFormat())
    {
        fclose(f);
        throw InvalidImageException("Inappropriate file format!\n");
    }
    mHeight=mBmih.height;
    mWidth=mBmih.width;
    mPixelArr = new Rgb*[mHeight];
    for(int i=0; i<mHeight; i++)
    {
        mPixelArr[i] = new Rgb[mWidth];
        fread(mPixelArr[i], 1, (mWidth*sizeof(Rgb)+3)&(-4), f);
    }
    fclose(f);
    this->filePath=filePath;
}

BmpFileHeader BmpImage::getFileHeader() noexcept
{
    return mBmfh;
}

BmpInfoHeader BmpImage::getInfoHeader() noexcept
{
    return mBmih;
}

void BmpImage::printPath() noexcept
{
    std::cout<<"Image path:\t"<<filePath<<std::endl;
}

void BmpImage::save()
{
    this->save(this->filePath);
}

void BmpImage::save(const std::string newFilePath)
{
    std::FILE *f = fopen(newFilePath.c_str(), "wb");
    if(f==nullptr)
    {
        throw InvalidImageException("Unable to save bmp file!\n");
    }
    fwrite(&mBmfh, 1, sizeof(BmpFileHeader), f);
    fwrite(&mBmih, 1, sizeof(BmpInfoHeader), f);
    for(int i=0; i<mHeight; i++)
    {
        fwrite(mPixelArr[i], 1, (mWidth*sizeof(Rgb)+3)&(-4), f);
    }
    fclose(f);
}

void BmpImage::resize(const int newWidth, const int newHeight, const Rgb defaultColor)
{
    if(newWidth<=0 || newHeight<=0)
        throw std::invalid_argument("Invalid new image size!");
    if (checkColor(defaultColor))
        throw std::invalid_argument("Non-Rgb color type!\n");
    int tempWidth=0, tempHeight=0;
    Rgb** temp=this->copy({0, 0}, {mWidth-1, mHeight-1}, tempHeight, tempWidth);
    for(int i=0;i<mHeight;i++)
        delete[] mPixelArr[i];
    delete[] mPixelArr;
    mPixelArr = new Rgb*[newHeight];
    for(int i=0;i<newHeight;i++)
    {
        mPixelArr[i]=new Rgb[newWidth];
        for(int j=0;j<newWidth;j++)
            mPixelArr[i][j]=defaultColor;
    }
    this->mHeight=newHeight;
    this->mWidth=newWidth;
    fileHeaderInit();
    infoHeaderInit();
    this->paste({0, 0}, temp, tempWidth, tempHeight);
    for(int i=0;i<tempHeight;i++)
        delete[] temp[i];
    delete[] temp;
}

int BmpImage::checkColor(Rgb color) noexcept
{
    return(color.r<0 || color.r>255 || color.b<0 || color.b>255 || color.g<0 || color.g>255);
}

void BmpImage::drawCircle(int radius, Point center, int thickness, Rgb lineColor, bool isFill, Rgb fillColor)
{
    center.y=mHeight-center.y-1;
    if(radius<0)
        throw std::invalid_argument("Negative radius!\n");
    if (thickness/2>radius)
        throw std::invalid_argument("Thickness is greater then radius\n");
    if(thickness<=0)
        throw std::invalid_argument("Non-positive thickness!\n");
    if (checkColor(lineColor))
        throw std::invalid_argument("Non-Rgb lineColor type!\n");
    if (checkColor(fillColor))
        throw std::invalid_argument("Non-Rgb fillColor type!\n");
    int leftBorder=0, rightBorder=mWidth-1, upBorder=mHeight-1, downBorder=0;
    if(center.y-radius-thickness/2>=0)
        downBorder=center.y-radius-thickness/2;
    if(center.y+radius+thickness/2<mHeight)
        upBorder=center.y+radius+thickness/2;
    if(center.x-radius-thickness/2>=0)
        leftBorder=center.x-radius-thickness/2;
    if(center.x+radius+thickness/2<mWidth)
        rightBorder=center.x+radius+thickness/2;
    for(int i=downBorder; i<=upBorder;i++)
    {
        if(i>=0 && i<mHeight)
        {
            for(int j=leftBorder; j<=rightBorder; j++)
            {
                if(j>=0 && j<mWidth)
                {
                    if(floor(sqrt(pow(i-center.y, 2)+pow(j-center.x, 2)))<=radius+thickness/2)
                    {
                        if(floor(sqrt(pow(i-center.y, 2)+pow(j-center.x, 2)))>=radius-thickness/2)
                            mPixelArr[i][j]=lineColor;
                        else if(isFill)
                            mPixelArr[i][j]=fillColor;
                    }
                }
            }
        }
    }
}

void BmpImage::checkZone(Point &leftUp, Point &rightDown) noexcept
{
    if(leftUp.x>rightDown.x)
    {
        int temp=leftUp.x;
        leftUp.x=rightDown.x;
        rightDown.x=temp;
    }
    if(leftUp.y>rightDown.y)
    {
        int temp=leftUp.y;
        leftUp.y=rightDown.y;
        rightDown.y=temp;
    }
}

void BmpImage::drawLine(Point leftUp, Point rightDown, int thickness, Rgb color)
{
    if(thickness<=0)
        throw std::invalid_argument("Non-positive thickness!\n");
    if (checkColor(color))
        throw std::invalid_argument("Non-Rgb color type!\n");
    leftUp.y=mHeight-leftUp.y-1;
    rightDown.y=mHeight-rightDown.y-1;
    int a=rightDown.y-leftUp.y;
    int b=leftUp.x-rightDown.x;
    int sign;
    if(abs(a)>abs(b))
        sign=1;
    else
        sign=-1;
    int f=0;
    int signa, signb;
    if (a < 0) 
        signa = -1;
    else 
        signa = 1;
    if (b < 0) 
        signb = -1;
    else 
        signb = 1;
    int x=leftUp.x;
    int y=leftUp.y;
    this->drawCircle(thickness/2, {x, mHeight-y-1}, 1, color, true, color);
    if(x!= rightDown.x || y!=rightDown.y)
    {
        if(sign==-1)
        {
            do
            {
                f+=a*signa;
                if(f>0)
                {
                    f-=b*signb;
                    y+=signa;
                }
                x-=signb;
                this->drawCircle(thickness/2, {x, mHeight-y-1}, 1, color, true, color);
            
            }
            while(x!= rightDown.x || y!=rightDown.y);
        }
        else
        {
            do
            {
                f+=b*signb;
                if(f>0)
                {
                    f-=a*signa;
                    x-=signb;
                }
                y+=signa;
                this->drawCircle(thickness/2, {x, mHeight-y-1}, 1, color, true, color);
            }
            while(x!=rightDown.x || y!=rightDown.y);
        }
    }
}

void BmpImage::drawRectangle(Point leftUp, Point rightDown, int thickness, Rgb lineColor, bool isFill, Rgb fillColor, bool smooth)
{
    checkZone(leftUp, rightDown);
    if(thickness<=0)
        throw std::invalid_argument("Non-positive thickness!\n");
    if (checkColor(lineColor))
        throw std::invalid_argument("Non-Rgb lineColor type!\n");
    if (checkColor(fillColor))
        throw std::invalid_argument("Non-Rgb fillColor type!\n");
    leftUp.y=mHeight-leftUp.y-1;
    rightDown.y=mHeight-rightDown.y-1;
    if(smooth==false)
    {
        for(int i=rightDown.y;i<=leftUp.y;i++)
            if(i>=0 && i<mHeight)
            {
                for(int j=leftUp.x;j<=rightDown.x;j++)
                    if(j>=0 && j<mWidth)
                    {
                        if(i<rightDown.y+thickness || i>leftUp.y-thickness || j<leftUp.x+thickness || j>rightDown.x-thickness)
                            mPixelArr[i][j]=lineColor;
                        else if(isFill)
                            mPixelArr[i][j]=fillColor;
                    }
            }
    }
    else
    {
        if(isFill)
        {
            for(int i=rightDown.y;i<=leftUp.y;i++)
                if(i>=0 && i<mHeight)
                {
                    for(int j=leftUp.x;j<=rightDown.x;j++)
                        if(j>=0 && j<mWidth)
                            mPixelArr[i][j]=fillColor;
                }
        }
        leftUp.y=mHeight-leftUp.y-1;
        rightDown.y=mHeight-rightDown.y-1;
        this->drawLine({leftUp.x, leftUp.y}, {rightDown.x, leftUp.y}, thickness, lineColor);
        this->drawLine({leftUp.x, leftUp.y}, {leftUp.x, rightDown.y}, thickness, lineColor);
        this->drawLine({rightDown.x, leftUp.y}, {rightDown.x, rightDown.y}, thickness, lineColor);
        this->drawLine({leftUp.x, rightDown.y}, {rightDown.x, rightDown.y}, thickness, lineColor);
    }
}

Rgb** BmpImage::copy(Point leftUp, Point rightDown, int &height, int &width) noexcept
{
    checkZone(leftUp, rightDown);
    if(leftUp.y<0)
        leftUp.y=0;
    if(leftUp.x<0)
        leftUp.x=0;
    if(rightDown.x>=mWidth)
        rightDown.x=mWidth-1;
    if(rightDown.y>=mHeight)
        rightDown.y=mHeight-1;
    if(leftUp.y>=mHeight || leftUp.x>=mWidth || rightDown.y<0 || rightDown.x<0)
    {
        height=0;
        width=0;
        return nullptr;
    }
    leftUp.y=mHeight-leftUp.y-1;
    rightDown.y=mHeight-rightDown.y-1;
    height=leftUp.y-rightDown.y+1;
    width=rightDown.x-leftUp.x+1;
    Rgb** copiedArray = new Rgb*[height];
    for(int i=rightDown.y;i<=leftUp.y;i++)
    {
        copiedArray[i-rightDown.y]= new Rgb[width];
        for(int j=leftUp.x;j<=rightDown.x;j++)
        {
            copiedArray[i-rightDown.y][j-leftUp.x]=mPixelArr[i][j];        
        }
    }
    return copiedArray;
}

void BmpImage::paste(Point leftUp, Rgb** arr, int width, int height) noexcept//width and height - sizes of arr 
{
    leftUp.y=mHeight-leftUp.y-1;
    for(int i=0; i<height;i++)
    {
        for(int j=0; j<width;j++)
        {
            if(leftUp.y-height+i+1>=0 && leftUp.y-height+i+1<mHeight && leftUp.x+j<mWidth && leftUp.x+j>=0)
            {
                mPixelArr[leftUp.y-height+1+i][j+leftUp.x]=arr[i][j];
            }
        }
    }
}

void invertPixel(Rgb &pixel)
{
    pixel.b=255-pixel.b;
    pixel.g=255-pixel.g;
    pixel.r=255-pixel.r;
}

void BmpImage::invertImage()
{
    for(int i=0;i<mHeight;i++)
        for(int j=0;j<mWidth;j++)
            invertPixel(mPixelArr[i][j]);
}

void makeGreyPixel(Rgb& pixel)
{
    int grey = static_cast<int>(0.299*static_cast<double>(pixel.r) + 0.587*static_cast<double>(pixel.r) + 0.114*static_cast<double>(pixel.b));
    pixel.b=grey;
    pixel.r=grey;
    pixel.g=grey;
}

void BmpImage::blackAndWhite()
{
    for(int i=0;i<mHeight;i++)
        for(int j=0;j<mWidth;j++)
            makeGreyPixel(mPixelArr[i][j]);
}

void BmpImage::mirror()
{
    for(int i=0; i<mHeight;i++)
    {
        for(int j=0;j<(mWidth/2);j++)
        {
            Rgb temp=mPixelArr[i][j];
            mPixelArr[i][j]=mPixelArr[i][mWidth-j-1];
            mPixelArr[i][mWidth-j-1]=temp;
        }
    }
} 
void BmpImage::circleOrnament(Rgb color)
{
    if (checkColor(color))
        throw std::invalid_argument("Non-Rgb color type!\n");
    int radius;
    if (mHeight>mWidth)
        radius=mWidth/2;
    else
        radius=mHeight/2;
    for(int i=0;i<mHeight;i++)
    {
        for(int j=0;j<mWidth;j++)
        {
            if(floor(sqrt(pow(i-(mHeight/2), 2)+pow(j-(mWidth/2), 2)))>radius)
                mPixelArr[i][j]=color;
        }
    }
}

void BmpImage::rectangleOrnament(Rgb color, int thickness, int count)
{
    if (checkColor(color))
        throw std::invalid_argument("Non-Rgb color type!\n");
    if(thickness<=0)
        throw std::invalid_argument("Non-positive thickness!\n");
    if(count<=0)
        throw std::invalid_argument("Non-positive count!\n");
    if(thickness> mWidth/2 || thickness> mHeight/2)
        throw std::invalid_argument("Too big thickness!\n");
    if(2*(thickness*2*count-1)>mWidth || 2*(thickness*2*count-1)>mHeight)
        throw std::invalid_argument("Too big count!\n");
    for(int i=0; i<count; i++)
    {
        this->drawRectangle({2*i*thickness, 2*i*thickness}, {mWidth-2*i*thickness-1, mHeight-2*i*thickness-1}, thickness, color);
    }
} 

void BmpImage::semiCircleOrnament(Rgb color, int thickness, int count)
{
    if (checkColor(color))
        throw std::invalid_argument("Non-Rgb color type!\n");
    if(thickness<=0)
        throw std::invalid_argument("Non-positive thickness!\n");
    if(count<=0)
        throw std::invalid_argument("Non-positive count!\n");
    int radiusWidth=ceil(static_cast<double>(mWidth)/(2.0*static_cast<double>(count)));
    int radiusHeight=ceil(static_cast<double>(mHeight)/(2.0*static_cast<double>(count)));
    if(radiusHeight<1 || radiusWidth<1)
        throw std::invalid_argument("Too big count!\n");
    if(radiusHeight<thickness || radiusWidth<thickness)
        throw std::invalid_argument("Too big thickness\n");
    for(int i=0;i<count;i++)
    {
        this->drawCircle(radiusHeight, {0, (2*i+1)*radiusHeight}, thickness, color);
        this->drawCircle(radiusHeight, {this->mWidth-1, (2*i+1)*radiusHeight}, thickness, color);
        this->drawCircle(radiusWidth, {(2*i+1)*radiusWidth, 0}, thickness, color);
        this->drawCircle(radiusWidth, {(2*i+1)*radiusWidth, this->mHeight-1}, thickness, color);
    }
} 

void BmpImage::drawRhombus(Point vertex, int size, Rgb fill_color)
{
    if (checkColor(fill_color))
        throw std::invalid_argument("Non-Rgb color type!\n");
    if(size<=0)
        throw std::invalid_argument("Non-positive size!\n");
    int a=floor(sqrt(pow(size, 2)/2.0));
    int j=0;
    for(int i=0; i<2*a;i++)
    {
        drawLine({vertex.x-j, vertex.y+i},{vertex.x+j, vertex.y+i}, 1, fill_color);
        if(i>a)
            j--;
        else
            j++;
    }
}

Point getRotationAxis(Point leftUp, Point rightDown, int width, int height)
{
    Point axis={(rightDown.x+leftUp.x)/2 - height/2, (rightDown.y+leftUp.y)/2 - width/2};
    return axis;
}

void BmpImage::rotate(Point leftUp, Point rightDown, int angle)
{
    int height=0, width=0;
    if(angle!=90 && angle!=180 && angle!=270)
        throw std::invalid_argument("Invalid rotation angle!");
    Rgb** pixelArray = this->copy(leftUp, {rightDown.x-1, rightDown.y-1}, height, width);
    if(angle==180)
    {
        Rgb** newPixelArray = new Rgb*[height];
        for(int i=0;i<height; i++)
            newPixelArray[i]=new Rgb[width];
        for(int i=0;i<height;i++)
            for(int j=0;j<width;j++)
                newPixelArray[i][j]=pixelArray[height-i-1][width-j-1];
        this->paste(leftUp, newPixelArray, width, height);
    }
    else
    {
        Rgb** newPixelArray = new Rgb*[width];
        for(int i=0;i<width; i++)
            newPixelArray[i]=new Rgb[height];
        if(angle==90)
        {
            for(int i=0;i<height;i++)
                for(int j=0;j<width;j++)
                    newPixelArray[j][i]=pixelArray[height-i-1][j];
        }
        else
        {
            for(int i=0;i<height;i++)
                for(int j=0;j<width;j++)
                    newPixelArray[j][i]=pixelArray[i][width-j-1];
        }
        this->paste(getRotationAxis(leftUp, rightDown, width, height), newPixelArray, height, width);
    }
}

BmpImage::~BmpImage()
{
    for(int i=0;i<mHeight;i++)
        delete[] mPixelArr[i];
    delete[] mPixelArr;
}