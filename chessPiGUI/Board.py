#! /usr/bin/python
# -*- coding: utf-8 -*-

from Tkinter import Tk, Canvas, Frame, Label, BOTH, PhotoImage
from time import sleep
from threading import Thread
import subprocess
from Stockfish import Stockfish

def ChessUpdate(board):
	engine = subprocess.Popen(
		'./chessPi',
		stdout=subprocess.PIPE,
		stdin=subprocess.PIPE)
	stockfish = Stockfish()
	while True:
		boardString = engine.stdout.readline().strip()
		print boardString
		if len(boardString) == 64:
			shadowString = engine.stdout.readline().strip()
			print shadowString
			board.drawBoard(boardString, shadowString, "")
		elif boardString == "hint":
			boardString = engine.stdout.readline().strip()
			shadowStrig = engine.stdout.readline().strip()
			fenString = engine.stdout.readline().strip()
			bestMove = stockfish.analyze(fenString)
			board.drawBoard(boardString, shadowStrig, bestMove)
			engine.stdin.write("ok")
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
		self.drawBoard(boardString, shadowString, "")
		

	def centerWindow(self):
		boardWidth = 208
		boardHeight = 208

		screenWidth = self.parent.winfo_screenwidth()
		screnHeight = self.parent.winfo_screenheight()
		centerWidth = (screenWidth)/2
		centerHeight =(screnHeight)/2

		self.parent.geometry('%dx%d+%d+%d' % (boardWidth, boardHeight, 
											  0, 0))

	def drawBoard(self, boardString, shadowString, hint):
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
		
		hintColumnSource = -1
		hintRowSource = -1
		hintColumnDest = -1
		hintRowDest = -1
		if hint:
			hintColumnSource = ord(hint[0])-ord('a')
			# because the board is printed from black (row 0) to white (row 7)
			# the row number needs to be inverted
			hintRowSource = 7 - (ord(hint[1])-ord('1'))
			hintColumnDest = ord(hint[2])-ord('a')
			hintRowDest = 7 -(ord(hint[3])-ord('1'))

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
				if col == hintColumnSource and row == hintRowSource or \
					 col == hintColumnDest and row == hintRowDest:
					border = "#0f0"
					interior = "#0f0"
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
