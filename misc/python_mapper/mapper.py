from tkinter import *

def draw_tile(c,x,y,color):
  print("{" + f"{x},{y}" +"},", end="")
  return c.create_rectangle(x,y,x+30,y+30,fill=color,outline="black")

def drawroutes(c,rects):
  c.create_rectangle(50,270,200,330, fill="pink")
  print("const Point name [24] = {",end="")
  # A ->
  x = 170
  y = 210
  for i in range(5):
    rects.append(draw_tile(c,x,y,"grey"))
    y-=30
  for j in range(16):
    rects.append(draw_tile(c,x,y,"grey"))
    x+=30
  for i in range(3):
    rects.append(draw_tile(c,x,y,"grey"))
    y+=30
  print("\b};\n\n const Point name [32] = {",end="")
  # A<-
  x = 100
  y = 220
  for i in range(7):
    rects.append(draw_tile(c,x,y,"green"))
    y-=30
  for j in range(20):
    rects.append(draw_tile(c,x,y,"green"))
    x+=30
  for i in range(5):
    rects.append(draw_tile(c,x,y,"green"))
    y+=30
  print("\b};\n\n const Point name [12] = {",end="")
  # R<-
  x = 615
  y = 115
  for i in range(5):
    rects.append(draw_tile(c,x,y,"red"))
    x-=30
  for j in range(7):
    rects.append(draw_tile(c,x,y,"red"))
    y+=30
  print("\b};\n\n const Point name [5] = {",end="")
  # R |
  x = 645
  y = 170
  for j in range(5):
    rects.append(draw_tile(c,x,y,"red"))
    y+=30
  print("\b};\n\n const Point name [12] = {",end="")
  # R ->
  x = 695
  y = 115
  for i in range(5):
    rects.append(draw_tile(c,x,y,"red"))
    x+=30
  for j in range(7):
    rects.append(draw_tile(c,x,y,"red"))
    y+=30
  


  
  print("\b};\n\n const Point name [12] = {",end="")
  # R<-
  x = 670
  y = 140
  for i in range(6):
    rects.append(draw_tile(c,x,y,"blue"))
    x-=30
  for j in range(6):
    rects.append(draw_tile(c,x,y,"blue"))
    y+=30
  print("\b};\n\n const Point name [5] = {",end="")
  # R |
  x = 675
  y = 170
  for j in range(5):
    rects.append(draw_tile(c,x,y,"blue"))
    y+=30
  print("\b};\n\n const Point name [11] = {",end="")
  # R ->
  x = 730
  y = 140
  for i in range(5):
    rects.append(draw_tile(c,x,y,"blue"))
    x+=30
  for j in range(6):
    rects.append(draw_tile(c,x,y,"blue"))
    y+=30
  print("\b};\n\n const Point name [5] = {",end="")
  # Bridge <-
  x = 470 
  y = 320
  for j in range(5):
    rects.append(draw_tile(c,x,y,"yellow"))
    y+=30
  print("\b};\n\n const Point name [5] = {",end="")
  # Bridge ->
  x = 860 
  y = 320
  for j in range(5):
    rects.append(draw_tile(c,x,y,"yellow"))
    y+=30
  print("\b};\n\n const Point name [5] = {",end="")
  # Bridge |
  x = 660 
  y = 320
  for j in range(5):
    rects.append(draw_tile(c,x,y,"yellow"))
    y+=30

  print("\b};\n\n const Point name [9] = {",end="")
  # R<-
  x = 460
  y = 470
  for i in range(4):
    rects.append(draw_tile(c,x,y,"red"))
    y+=30
  for i in range(5):
    rects.append(draw_tile(c,x,y,"red"))
    x+=30
  print("\b};\n\n const Point name [4] = {",end="")
  # R |
  x = 645
  y = 470
  for i in range(4):
    rects.append(draw_tile(c,x,y,"red"))
    y+=30
  print("\b};\n\n const Point name [11] = {",end="")
  # R ->
  x = 840
  y = 470
  for i in range(4):
    rects.append(draw_tile(c,x,y,"red"))
    y+=30
  for i in range(7):
    rects.append(draw_tile(c,x,y,"red"))
    x-=30
  print("\b};\n\n const Point name [32] = {",end="")
  # B <-
  x = 620
  y = 590
  for i in range(4):
    rects.append(draw_tile(c,x,y,"grey"))
    y+=30
  for i in range(20):
    rects.append(draw_tile(c,x,y,"grey"))
    x+=30
  for i in range(8):
    rects.append(draw_tile(c,x,y,"grey"))
    y-=30
  print("\b};\n\n const Point name [9] = {",end="")
  # R<-
  x = 480
  y = 485
  for i in range(3):
    rects.append(draw_tile(c,x,y,"blue"))
    y+=30
  for i in range(6):
    rects.append(draw_tile(c,x,y,"blue"))
    x+=30
  print("\b};\n\n const Point name [4] = {",end="")
  # R |
  x = 675
  y = 470
  for i in range(4):
    rects.append(draw_tile(c,x,y,"blue"))
    y+=30
  print("\b};\n\n const Point name [10] = {",end="")
  # R ->
  x = 870
  y = 485
  for i in range(4):
    rects.append(draw_tile(c,x,y,"blue"))
    y+=30
  for i in range(6):
    rects.append(draw_tile(c,x,y,"blue"))
    x-=30
  print("\b};\n\n const Point name [23] = {",end="")
  # B ->
  x = 675
  y = 600
  for i in range(2):
    rects.append(draw_tile(c,x,y,"green"))
    y+=30
  for i in range(15):
    rects.append(draw_tile(c,x,y,"green"))
    x+=30
  for i in range(6):
    rects.append(draw_tile(c,x,y,"green"))
    y-=30



  print("\b};\n")


def game():
  main = Tk()
  main.geometry("1360x760+100+100")
  c = Canvas(main,height = 760, width=1360)
  c.pack()
  img = PhotoImage(file="../imgs/Fondo.png")
  c.create_image(1360/2,760/2,image=img)
  rects = []
  drawroutes(c,rects)
  main.mainloop()

game()