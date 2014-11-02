#! /usr/bin/python
# -*- coding: utf-8 -*-

from Tkinter import Tk, Canvas, Frame, Label, BOTH, PhotoImage
from time import sleep
from threading import Thread
import subprocess

def ChessUpdate(board):
	engine = subprocess.Popen(
		'./chessPi',
		stdout=subprocess.PIPE)
	while True:
		boardString = engine.stdout.readline()
		boardString = boardString.strip()
		print boardString
		if len(boardString) == 64:
			shadowString = engine.stdout.readline()
			shadowString = shadowString.strip()
			print shadowString
			board.drawBoard(boardString, shadowString)
		elif boardString == "exit":
			break

class Board(Frame):

	def __init__(self, parent):
		Frame.__init__(self, parent)
		self.parent = parent
		self.initUI()

	def initUI(self):
		self.parent.title("Board")
		self.pack(fill=BOTH, expand=1)
		self.centerWindow()

		pieceNames = "rnbqkpPRNBQK"
		self.pieces = {}
		for pieceName in pieceNames:
			self.pieces[pieceName] = PhotoImage(file='01_imgs/' + pieceName +'.gif')
		
		self.canvas = Canvas(self)
		self.canvas.pack(fill=BOTH, expand=1)
		boardString = "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";
		shadowString= "1111111111111111000000000000000000000000000000001111111111111111"
		self.drawBoard(boardString, shadowString)
		

	def centerWindow(self):
		boardWidth = 208
		boardHeight = 208

		screenWidth = self.parent.winfo_screenwidth()
		screnHeight = self.parent.winfo_screenheight()
		centerWidth = (screenWidth)/2
		centerHeight =(screnHeight)/2

		self.parent.geometry('%dx%d+%d+%d' % (boardWidth, boardHeight, 
											  0, 0))

	def drawBoard(self, boardString, shadowString):
		isWhite = True
		squareWidth = 26
		squareHeight = 26
		topX = 0
		topY = 0
		bottomX = 26
		bottomY = 26
		border = "#fff"
		interior = "#fff"
		self.canvas.delete("all")

		for row in range(8):
			for col in range(8):
				if(isWhite):
					border = "#fc9"
					interior = "#fc9"
				else:
					border = "#931"
					interior = "#931"
				pieceName = boardString[row*8 + col]
				shadow = shadowString[row*8 + col]
				if pieceName == '.' and shadow == '1' or pieceName != '.' and shadow == '0':
					border = "#f00"
					interior = "#f00"
				self.canvas.create_rectangle((topX + (squareWidth*col)),
										(topY + (squareHeight*row)),
										(bottomX + (squareWidth*col)),
										(bottomY + (squareHeight*row)),
									    outline=border, fill=interior)
				if pieceName != '.':
					self.canvas.create_image(13 + 26*col, 13 + 26*row, image=self.pieces[pieceName])
				isWhite = not isWhite
					
			isWhite = not isWhite
		

def main():
	root= Tk()
	root.overrideredirect(1) # Remove title bar of window in GUI
	board = Board(root)
	chessUpdate = Thread(target = ChessUpdate, args = (board,))
	chessUpdate.start()
	root.mainloop()
	


if __name__ == '__main__':
	main()	
