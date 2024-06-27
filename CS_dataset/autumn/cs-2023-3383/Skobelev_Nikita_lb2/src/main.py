import PIL
from PIL import Image, ImageDraw
def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line((x0, y0, x1, y1), fill, width)
    return image


def check_coords(image, x0, y0, x1, y1):
    w,h=image.size
    if 0 <= x0 < w and h > y0 >= 0 and 0 <= x1 < w and h > y1 >= 0 and  y0 < y1 and x0 < x1:
        return True
    else:
        return False


def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        image2 = image.crop((x0, y0, x1, y1))
        image2 = image2.convert('1')
        image.paste(image2, (x0, y0, x1, y1))
    return image


def find_rect_and_recolor(image, old_color, new_color):
    pix = image.load()
    w,h=image.size
    data = [[1]*(w) for i in range(h)]
    for y in range(h):
        for x in range(w):
            if(pix[x,y]==old_color):data[y][x]=0
    dp=[0]*w
    ans = 0
    coord =(0,0,0,0)
    for i in range(h):
        for j in range(w):
            if(data[i][j]==1):dp[j]=0
            else: dp[j]+=1
            if(dp[j]!=0):
                left=j
                right=j
                while left-1>=0 and dp[left-1]>=dp[j]:left-=1
                while right+1<w and dp[right+1]>=dp[j]:right+=1
                if ans<(right-left+1)*dp[j]:
                    ans=(right-left+1)*dp[j]
                    coord=(left,i-dp[j]+1,right,i)
    drawing = ImageDraw.Draw(image)
    drawing.rectangle(coord, new_color)
    return image