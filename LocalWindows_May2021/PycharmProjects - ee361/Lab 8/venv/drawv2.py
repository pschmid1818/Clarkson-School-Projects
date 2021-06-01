import turtle
import math

def sin(x):
    return math.sin(x)

def cos(y):
    return math.cos(y)

def rad(angle):
    return math.radians(angle)

class Canvas:
    def __init__(self, w, h):
        self.__visibleObjects = []   #list of shapes to draw
        self.__turtle = turtle.Turtle()
        self.__screen = turtle.Screen()
        self.__screen.setup(width = w, height = h)
        #self.__turtle.hideturtle()

    def drawAll(self):
        self.__turtle.reset()
        self.__turtle.up()
        self.__screen.tracer(0)
        for shape in self.__visibleObjects: #draw all shapes in order
            shape._draw(self.__turtle)
        self.__screen.tracer(1)
        self.__turtle.hideturtle()

    def addShape(self, shape):
        self.__visibleObjects.append(shape)

    def draw(self, gObject):
        gObject.setCanvas(self)
        gObject.setVisible(True)
        self.__turtle.up()
        self.__screen.tracer(0)
        gObject._draw(self.__turtle)
        self.__screen.tracer(1)
        self.addShape(gObject)

from abc import *
class GeometricObject(ABC):
    def __init__(self):
        self.__lineColor = 'black'
        self.__lineWidth = 1
        self.__visible = False
        self.__myCanvas = None

    def setColor(self, color):  #modified to redraw visible shapes
        self.__lineColor = color
        if self.__visible:
            self.__myCanvas.drawAll()

    def setWidth(self, width):  #modified to redraw visible shapes
        self.__lineWidth = width
        if self.__visible:
            self.__myCanvas.drawAll()

    def getColor(self):
        return self.__lineColor

    def getWidth(self):
        return self.__lineWidth

    @abstractmethod
    def _draw(self):
        pass

    def setVisible(self, vFlag):
        self.__visible = vFlag

    def getVisible(self):
        return self.__visible

    def setCanvas(self, theCanvas):
        self.__myCanvas = theCanvas

    def getCanvas(self):
        return self.__myCanvas

class Point(GeometricObject):
    def __init__(self, x, y):
        super().__init__()
        self.__x = x
        self.__y = y

    def getCoord(self):
        return (self.__x, self.__y)

    def getX(self):
        return self.__x

    def getY(self):
        return self.__y

    def _draw(self, turtle):
        turtle.goto(self.__x, self.__y)
       # turtle.dot(self.__lineWidth, self.__lineColor)
        turtle.dot(self.getWidth(), self.getColor())

class Shape(GeometricObject):
    def __init__(self):
        super().__init__()
        self.__fillColor = 'magenta'

    def setFillColor(self,color):
        self.__fillColor = color

    def getFillColor(self):
        return self.__fillColor


class Polygon(Shape):
    def __init__(self):
        super().__init__()
        self.__PointList = []

    def addPoint(self, point):
        self.__PointList.append(point)

    def getPoints(self):
        return self.__PointList

    def _draw(self, turtle):
        for ii in range(len(self.__PointList)):
            point = self.__PointList[ii]
            pointX = point.getX()
            pointY = point.getY()
            if ii == 0:
                turtle.penup()
                turtle.goto(pointX,pointY)
                turtle.pendown()
            else:
                turtle.goto(pointX,pointY)
        turtle.penup()

class Rectangle(Polygon):

    def __init__(self, lowerLeft, upperRight):
        super().__init__()
        self.__lowerLeft = self.addPoint(lowerLeft), lowerLeft
        self.__upperRight = self.addPoint(upperRight), upperRight


    def getLowerLeft(self):
        return self.__lowerLeft

    def getUpperRight(self):
        return self.__upperRight

    def _draw(self, turtle):
        turtle.penup()
        turtle.goto(self.__lowerLeft.getX(), self.__lowerLeft.getY)
        turtle.pendown()
        turtle.goto(self.__upperRight.getX(), self.__lowerLeft.getY())
        turtle.goto(self.__upperRight.getX(), self.__upperRight.getY())
        turtle.goto(self.__lowerLeft.getX(), self.__upperRight.getY())
        turtle.goto(self.__lowerLeft.getX(), self.__lowerLeft.getY())


class Line(Shape):
    def __init__(self, p1, p2):
        super().__init__()
        self.__p1 = p1
        self.__p2 = p2

    def getP1(self):
        return self.__p1

    def getP2(self):
        return self.__p2

    def _draw(self, turtle):
        turtle.color(self.getColor())
        turtle.width(self.getWidth())
        turtle.up()
        turtle.goto(self.__p1.getCoord())
        turtle.down()
        turtle.goto(self.__p2.getCoord())

def test2():
    myCanvas = Canvas(500, 500)
    line1 = Line(Point(-100, -100), Point(100, 100))
    line2 = Line(Point(-100, 100), Point(100, -100))
    line1.setWidth(4)
    myCanvas.draw(line1)
    myCanvas.draw(line2)
    line1.setColor('red')


class Ellipse(Shape):
    def __init__(self, center, height, width, tilt):
        super().__init__()
        self.__center = center
        self.__height = height
        self.__width = width
        self.__tilt = tilt

    def getCenter(self):
        x = self.__center.getX()
        y = self.__center.getY()

        return (x, y)

    def getHeight(self):
        return self.__height

    def getWidth(self):
        return self.__width

    def getAngle(self):
        return self.__tilt

    def _draw(self, turtle):
        # creen = turtle.Screen()
        # screen.setup(1000, 1000)
        # screen.title("General Ellipse with Parametric Equation - PythonTurtle.Academy")
        # screen.tracer(0, 0)

        turtle.speed(0)
        turtle.hideturtle()
        turtle.up()

        n = 2000

        # (cx,cy): center of ellipse, a: width, b:height, angle: tilt
        # draw the first point with pen up
        t = 0
        x = self.__center.getX() + self.__width * math.cos(t) * math.cos(math.radians(self.__tilt)) - self.__height * math.sin(t) * math.sin(math.radians(self.__tilt))
        y = self.__center.getY() + self.__width * math.cos(t) * math.sin(math.radians(self.__tilt)) + self.__height * math.sin(t) * math.cos(math.radians(self.__tilt))
        turtle.up()
        turtle.goto(x, y)
        turtle.down()
        turtle.color('red')
        # draw the rest with pen down
        for i in range(n):
            x = self.__center.getX() + self.__width * math.cos(t) * math.cos(
                math.radians(self.__tilt)) - self.__height * math.sin(t) * math.sin(math.radians(self.__tilt))
            y = self.__center.getY() + self.__width * math.cos(t) * math.sin(
                math.radians(self.__tilt)) + self.__height * math.sin(t) * math.cos(math.radians(self.__tilt))

            turtle.goto(x, y)
            t += 2 * math.pi / n


class Circle(Ellipse):
    def __init__(self,center,radius):
        super().__init__(center, radius, radius,0)
        self.__center = center
        self.__radius = radius

    def getCenter(self):
        x = self.__center.getX()
        y = self.__center.getY()
        return (x, y)

    def getRadius(self):
        return self.__radius

    def _draw(self, turtle):

        turtle.penup()
        turtle.goto(self.__center.getX(), self.__center.getY() + self.__radius)
        turtle.pendown()
        turtle.circle(self.__radius)


def drawHouse():

  myCanvas = Canvas(800, 600)                           #create a canvas
  #house = Rectangle((Point(-100, -100), Point(100, 100)))        #draw a rectangle from 2 points
  #house.setFill('blue')   #fill with color
  #door = Rectangle((Point(-50, -100), Point(0, 75)))
  #door.setFill('brown')
  roof1 = Line(Point(-100, 100), Point(0, 200))  #draw a line from 2 points
  roof2 = Line(Point(0, 200), Point(100, 100))
  roof1.setWidth(3)            #set line width
  roof2.setWidth(3)
  #myCanvas.draw(house)
  #myCanvas.draw(door)
  myCanvas.draw(roof1)
  myCanvas.draw(roof2)
  sun = Circle(Point(150, 250), 20)  #draw a  circle from point and radius
  #sun.setFill('yellow')
  myCanvas.draw(sun)
  turtle.penup()




if __name__ == '__main__':

    test = Ellipse(Point(0,0), 40,20, 0)
    test3 = Circle(Point(20,20),40)
    #test4 = drawHouse()
    test5 = Rectangle(Point(20,100), Point(40,50))
    mycanvas = Canvas(800,500)
    mycanvas.draw(test5)