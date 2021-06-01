from cImage import *

def halfImage(oldImage):
    oldW = oldImage.getWidth()
    oldH = oldImage.getHeight()

    newIm = EmptyImage(oldW//2, oldH//2)

    for row in range(oldH):
        for col in range(oldW):
            oldPixel = oldImage.getPixel(col, row)
            if col % 2 == 1 and row % 2 == 1:
                newIm.setPixel(col//2,     row//2,     oldPixel)

    return newIm



def makeHalfImage(imageFile):
    oldImage = FileImage(imageFile)
    width = oldImage.getWidth()
    height = oldImage.getHeight()

    myWin = ImageWin("Half Size", width * 1, height * 1.5)
    oldImage.draw(myWin)

    newImage = halfImage(oldImage)
    newImage.setPosition(0, oldImage.getHeight() + 1)
    newImage.draw(myWin)

    myWin.exitOnClick()

if __name__ == '__main__':
    makeHalfImage('castle.gif')