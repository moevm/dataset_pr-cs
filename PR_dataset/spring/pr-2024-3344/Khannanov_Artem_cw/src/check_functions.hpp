int 
checkMirrorValues (std::vector <std::pair<std::string, std::string>> dict, Rgb** arr, int H, int W);

int 
checkCopyValues(std::vector <std::pair<std::string, std::string>> dict, Rgb** arr, int H, int W);

int
checkReplaceValues(std::vector <std::pair<std::string, std::string>> dict, Rgb** arr, int H, int W);

int
checkFilterValues(std::vector <std::pair<std::string, std::string>> dict, Rgb** arr, int H, int W);

int
checkCircleValues(std::vector <std::pair<std::string, std::string>> dict, Rgb** arr, int H, int W);

int 
checkLineValues(std::vector <std::pair<std::string, std::string>> dict, Rgb** arr, int H, int W);

int 
checkAValues(std::vector <std::pair<std::string, std::string>> dict, Rgb** arr, BitmapInfoHeader bmif, BitmapFileHeader bmfh, std::string file);