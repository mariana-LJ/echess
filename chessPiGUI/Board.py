#! /usr/bin/python
# -*- coding: utf-8 -*-

from Tkinter import Tk, Canvas, Frame, BOTH

class Board(Frame):

	def __init__(self, parent):
		Frame.__init__(self, parent)

		self.parent = parent
		self.initUI()

	def initUI(self):
		
		self.parent.title("Board")
		self.pack(fill=BOTH, expand=1)
		self.centerWindow()
		self.drawBoard()
		

	def centerWindow(self):
		
		boardWidth = 520
		boardHeight = 520

		screenWidth = self.parent.winfo_screenwidth()
		screnHeight = self.parent.winfo_screenheight()

		centerWidth = (screenWidth)/2
		centerHeight =(screnHeight)/2

		self.parent.geometry('%dx%d+%d+%d' % (boardWidth, boardHeight, 
											  centerWidth, centerHeight))

	def drawBoard(self):
		
		isWhite = True
		squareWidth = 60
		squareHeight = 60
		topX = 20
		topY = 20
		bottomX = 80
		bottomY = 80
		border = "#fff"
		interior = "#fff"
		
		canvas = Canvas(self)
		for row in range(8):
			for col in range(8):
				if(isWhite):
					border = "#fff"
					interior = "#fff"
				else:
					border = "#000"
					interior = "#000"
				canvas.create_rectangle((topX + (squareWidth*col)),
										(topY + (squareHeight*row)),
										(bottomX + (squareWidth*col)),
										(bottomY + (squareHeight*row)),
									    outline=border, fill=interior)
				isWhite = not isWhite
			isWhite = not isWhite

		canvas.pack(fill=BOTH, expand=1)	
		

def main():
		
	root= Tk()
	b = Board(root)
	root.mainloop()


if __name__ == '__main__':
	main()	
