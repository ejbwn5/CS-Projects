import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backend_bases import MouseButton
import math

bezierControls = [] #initially no control points

showPoints = True #whether or not to show points

connectedEndpoints = False

curveResolution = 100 # amount of line segments to make each curve out of

def drawPoints():
  global bezierControls
  global plt
  if not showPoints:
    return None
  
  x = [val[0][0] for val in bezierControls]
  y = [val[0][1] for val in bezierControls]
  plt.scatter(x, y, color="red") #draw points
  
  x = []
  y = []  
  
  for val in bezierControls: 
    angle = val[1] #get angle between point and its handles
    
    newX = val[0][0]
    newY = val[0][1]
    newX -= val[2][0] * math.cos(angle)
    newY -= val[2][0] * math.sin(angle) #get entering handles position
    x += [newX]
    y += [newY] #add it to list
    
    newX = val[0][0]
    newY = val[0][1]
    newX += val[2][1] * math.cos(angle)
    newY += val[2][1] * math.sin(angle) #get exiting handles position
    x += [newX]
    y += [newY] #add it to list
    
  plt.scatter(x, y, color="orange")  #draw control handles
  
#finds angle between two points
def angleBetweenPoints(p1, p2):  
  tanVal = math.atan((p2[1]-p1[1])/(p2[0]-p1[0]))
  
  if p2[0] < p1[0]:
    tanVal += math.pi
  
  tanVal = tanVal % (2*math.pi) #force bounds to be 0 to 2pi
  
  return tanVal
  
#linear interpolation between two points
#amt should be between 0.0 and 1.0
def lerp(start, end, amt):  
  return (start[0] + (end[0]-start[0]) * amt, start[1] + (end[1]-start[1]) * amt)

def bezier(bezierControls, divisions):
  global plt
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
  global connectedEndpoints
  
  indices = list(range(len(bezierControls)-1))
  if connectedEndpoints and len(bezierControls) > 1:
    indices = [-1] + indices
  
  for i in indices: #draw a separate cubic bezier curve between each pair of points
    pts = []
    val = bezierControls[i] #bezier point #1
    
    pts += [(val[0])] #add the first point itself  
    
    #then add its exiting handle
    pts += [(val[0][0] + math.cos(val[1]) * val[2][1], val[0][1] + math.sin(val[1]) * val[2][1])]    
        
        
    val = bezierControls[i+1] #bezier point #2
    
    #add its entering handle
    pts += [(val[0][0] - math.cos(val[1]) * val[2][0], val[0][1] - math.sin(val[1]) * val[2][0])] 
    
    #then finally its actual point
    pts += [(val[0])]    
    
    points = bezier(pts, divisions=curveResolution) #get points of the cubic bezier curve
    x = [val[0] for val in points]
    y = [val[1] for val in points]    
    plt.plot(x, y, color="blue") #draw it
  #if connectedEndpoints:


mousePos = [0,0]
mouseDown = False 
isHandle = False #whether or not the thing we're dragging is a control handle
handleNum=0 #which handle are we dragging?
selectedPoint = 0 #index of the bezierControls list

#use to find nearest point, only squared distance since we're just comparing and sqrt functions are inefficient
def sqrDist(a,b):
  return ((b[0]-a[0])**2 + (b[1]-a[1])**2)

def drawStuff():
  global plt
  plt.clf() #clear graph  
  plt.title('Composite Cubic Bezier Curve') #give title  
  plt.ylim(0,100) #set bounds
  plt.xlim(0,100)
  drawPoints()
  drawCurve()
  
def on_move(event):
  global bezierControls
  global showPoints
  global isHandle
  global handleNum
  global selectedPoint
  global mousePos
  global mouseDown
  
  if not showPoints:
    return None
  
  if event.inaxes:
    
    mousePos = (event.xdata, event.ydata) #update mouse position variable
    
    if mouseDown: #we're dragging a point
      
      if not isHandle:
        #simply move the root position      
        newthing = [mousePos, bezierControls[selectedPoint][1], bezierControls[selectedPoint][2]]        
        bezierControls = bezierControls[:selectedPoint] + [newthing] + bezierControls[selectedPoint+1:]
      else:        
        angle = angleBetweenPoints(bezierControls[selectedPoint][0], mousePos) #find the angle between the mouse and the root pos
        
        if handleNum == 0: #the angle needs to be adjusted by 180 degrees if its the entering handle
          angle = (angle + math.pi) % (2*math.pi)
        
        distance = list(bezierControls[selectedPoint][2]) #original distances
        
        #calculate new distance for the specified handle
        distance[handleNum] = sqrDist(bezierControls[selectedPoint][0], mousePos) ** 0.5
        
        distance = tuple(distance) #convert back to tuple       
        
        newthing = [bezierControls[selectedPoint][0], angle, distance] #bezier point to replace old with
        
        bezierControls = bezierControls[:selectedPoint] + [newthing] + bezierControls[selectedPoint+1:]
        
      drawStuff() #redraw screen

def on_click(event):
  global isHandle
  global handleNum
  global selectedPoint
  global bezierControls
  global mouseDown
  global mousePos
  
  if not showPoints: #don't let user add or move points when theyre invisible because that's just weird
    return None
    
  mousePos = [event.xdata, event.ydata] #update mouse position variable
  if mousePos[0] == None or mousePos[1] == None:   
    return None
  
  if event.button is MouseButton.LEFT:            
    minDist = None #initialize minimums to None
    minPointInd = None    
        
    #find nearest point
    for point in range(len(bezierControls)):
      d = sqrDist(mousePos, bezierControls[point][0])
      if minDist == None or d < minDist:
        minDist = d
        minPointInd = point
      
    if minDist == None: #no points exist at all yet
      return None
      
    #ensure its at least within 2 units of the nearest point
    if minDist < 4:
      selectedPoint = minPointInd
      isHandle=False
      mouseDown = True   
      return None
    
    
    #see if we grabbled a handle
    
    for point in range(len(bezierControls)):    
      val = bezierControls[point]
      
      #check entering handles
      d = sqrDist(mousePos, (val[0][0] - val[2][0] * math.cos(val[1]), val[0][1] - val[2][0] * math.sin(val[1]))) 
      if minDist == None or d < minDist:
        minDist = d
        minPointInd = [point, 0]
      
      #check exiting handles
      d = sqrDist(mousePos, (val[0][0] + val[2][1] * math.cos(val[1]), val[0][1] + val[2][1] * math.sin(val[1])))
      if minDist == None or d < minDist:
        minDist = d
        minPointInd = [point, 1]
    
    if minDist < 4: #we found a handle to grab
      selectedPoint = minPointInd[0]
      isHandle = True
      handleNum = minPointInd[1]
      mouseDown = True   
      
    
  elif event.button is MouseButton.RIGHT: #add new point     
    angle = 0 #initialize the angle to be 0 degrees    
    
    if len(bezierControls) > 0: #make the initial angle the angle between the new position and the last control point, if one exists
      angle = angleBetweenPoints(bezierControls[-1][0], mousePos)
    
    bezierControls += [[mousePos, angle, [10,10]]]
    selectedPoint = len(bezierControls) - 1
    isHandle = False
    mouseDown = True
    drawStuff() #redraw screen
    
def on_clickRelease(event):
  global mouseDown
  if event.button is MouseButton.LEFT or event.button is MouseButton.RIGHT:
    mouseDown = False

def on_keypress(event):    
  global bezierControls 
  global connectedEndpoints  
  global selectedPoint 
  global showPoints
  if event.key == 'backspace':
    bezierControls = []
    drawStuff() #redraw screen
  elif event.key == 'delete':
    if selectedPoint != None:
      bezierControls = bezierControls[:selectedPoint] + bezierControls[selectedPoint+1:] #remove the last selected point
      selectedPoint = None
      drawStuff()
  elif event.key == ' ': #toggle the point visibility
    showPoints = not showPoints
    drawStuff()
  elif event.key == 'c': #toggle endpoint connection
    connectedEndpoints = not connectedEndpoints
    drawStuff()
    
#set up mouse event handlers
binding_id = plt.connect('motion_notify_event', on_move)
plt.connect('button_press_event', on_click)
plt.connect('button_release_event', on_clickRelease)
plt.connect('key_press_event', on_keypress)

plt.ion() #set to be interractive so the plot keeps updating

drawStuff() #do the initial draw

plt.show(block = True) #plot the graph and block until the window is closed