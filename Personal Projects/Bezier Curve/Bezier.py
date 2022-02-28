import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backend_bases import MouseButton

bezierControls = [] #initially no control points

curveResolution = 100 # amount of line segments to make the curve out of

def drawPoints():
  global bezierControls
  global plt
  x = [val[0] for val in bezierControls]
  y = [val[1] for val in bezierControls]
  plt.scatter(x, y, color="red") 

#linear interpolation between two points
#amt should be between 0.0 and 1.0
def lerp(start, end, amt):  
  return (start[0] + (end[0]-start[0]) * amt, start[1] + (end[1]-start[1]) * amt)

def bezier(bezierControls, divisions):
  global plt
  global debug
  if len(bezierControls) < 2: #need at least 2 control points    
    return []
  timeStepResolution = 1/divisions
  points = [] #list of points to connect for the curve
  for segment in range(len(bezierControls)-1): #each line segment between control points
    newVal = []    
    for t in (list(np.arange(0, 1, timeStepResolution)) + [1.0]):
      newVal += [lerp(bezierControls[segment], bezierControls[segment+1], t)]
    points += [newVal] #get list of lerped points between control segments
  
  while len(points) > 1: #repeatedly get new curves by lerping between existing curves between control points until we're left with one curve    
    newVals = []    
    for i in range(len(points)-1):
      newV = []      
      for t in range(len(points[i])):
        newV += [lerp(points[i][t], points[i+1][t], t * timeStepResolution)]
      newVals += [newV]  
    points = newVals
  return points[0] #return the list of points

def drawCurve():
  global bezierControls
  global plt
  points = bezier(bezierControls, divisions=curveResolution) 
  x = [val[0] for val in points]
  y = [val[1] for val in points]    
  plt.plot(x, y, color="blue")
  
mousePos = [0,0]
mouseDown = False 
selectedPoint = 0 #index of the bezierControls list

def drawStuff():
  global plt
  plt.clf() #clear graph  
  plt.title('Bezier Curve') #give title  
  plt.ylim(0,100) #set bounds
  plt.xlim(0,100)
  drawPoints()
  drawCurve()
  
def on_move(event):
  global bezierControls
  global selectedPoint
  global mousePos
  global mouseDown
  if event.inaxes:
    # get the x and y pixel coords
    x, y = event.x, event.y
    ax = event.inaxes  # the axes instance
    
    mousePos = [event.xdata, event.ydata] #update mouse position variable
    
    if mouseDown: #we're dragging a point
    
      #update the list of control points
      bezierControls = bezierControls[:selectedPoint] + [mousePos] + bezierControls[selectedPoint+1:]
      
      drawStuff() #redraw screen

#use to find nearest point, only squared distance since we're just comparing and sqrt functions are inefficient
def sqrDist(a,b):
  return ((b[0]-a[0])**2 + (b[1]-a[1])**2)

def on_click(event):
  global selectedPoint
  global bezierControls
  global mouseDown
  global mousePos
  
  mousePos = [event.xdata, event.ydata] #update mouse position variable
  
  if event.button is MouseButton.LEFT:            
    minDist = None #initialize minimums to None
    minPointInd = None    
        
    #find nearest point
    for point in range(len(bezierControls)):
      d = sqrDist(mousePos, bezierControls[point])
      if minDist == None or d < minDist:
        minDist = d
        minPointInd = point
      
    if minDist == None: #no points exist at all yet
      return None
      
    #ensure its at least within 2 units of the nearest point
    if minDist < 4:
      selectedPoint = minPointInd
      mouseDown = True            
  elif event.button is MouseButton.RIGHT: #add new point
    bezierControls += [mousePos]
    selectedPoint = len(bezierControls) - 1
    mouseDown = True
    drawStuff() #redraw screen
    
def on_clickRelease(event):
  global mouseDown
  if event.button is MouseButton.LEFT or event.button is MouseButton.RIGHT:
    mouseDown = False

def on_keypress(event):    
  global bezierControls  
  if event.key == 'delete' or event.key == 'backspace':
    bezierControls = []
    drawStuff() #redraw screen

#set up mouse event handlers
binding_id = plt.connect('motion_notify_event', on_move)
plt.connect('button_press_event', on_click)
plt.connect('button_release_event', on_clickRelease)
plt.connect('key_press_event', on_keypress)

plt.ion() #set to be interractive so the plot keeps updating

drawStuff() #do the initial draw
plt.show(block = True) #plot the graph and block until the window is closed