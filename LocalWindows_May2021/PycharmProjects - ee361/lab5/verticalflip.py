from cImage import *


def verticalFlip(oldImage):
    oldW = oldImage.getWidth()
    oldH = oldImage.getHeight()

    newIm = EmptyImage(oldW, oldH)

    maxP = oldW - 1
    for row in range(oldH):
        for col in range(oldW):
            oldPixel = oldImage.getPixel(maxP - col, row)

            newIm.setPixel(col, row, oldPixel)

    return newIm


def makeFlip(imageFile):
    oldImage = FileImage(imageFile)
    width = oldImage.getWidth()
    height = oldImage.getHeight()

    myWin = ImageWin("Vertical Flip", width * 2, height)
    oldImage.draw(myWin)

    newImage = verticalFlip(oldImage)
    newImage.setPosition(width + 1, 0)
    newImage.draw(myWin)

    myWin.exitOnClick()


if __name__ == '__main__':
    makeFlip('castle.gif')