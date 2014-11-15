#! /usr/bin/python
# -*- coding: utf-8 -*-

from Tkinter import Tk, Canvas, Frame, Label, BOTH, PhotoImage
from time import sleep
from threading import Thread
import subprocess
from Stockfish import Stockfish

def ChessUpdate(board):
	chessPi = subprocess.Popen(
		'./chessPi',
		stdout=subprocess.PIPE,
		stdin=subprocess.PIPE)
	stockfish = Stockfish()
	while True:
		command = chessPi.stdout.readline().strip()
		if command == "move" or command == "error":
			boardString = chessPi.stdout.readline().strip()
			shadowString = chessPi.stdout.readline().strip()
			turn = chessPi.stdout.readline().strip()
			print boardString
			print shadowString
			board.drawBoard(boardString, shadowString, "", "", turn, command)
		elif command == "hint":
			boardString = chessPi.stdout.readline().strip()
			shadowStrig = chessPi.stdout.readline().strip()
			turn = chessPi.stdout.readline().strip()
			fenString = chessPi.stdout.readline().strip()
			board.drawBoard(boardString, shadowStrig, "", "", turn, command)
			bestMove = stockfish.analyze(fenString)
			board.drawBoard(boardString, shadowStrig, bestMove, "", turn, "nocommand")
			chessPi.stdin.write("ok\n")
		elif command == "option":
			boardString = chessPi.stdout.readline().strip()
			shadowStrig = chessPi.stdout.readline().strip()
			turn = chessPi.stdout.readline().strip()
			option = chessPi.stdout.readline().strip()
			board.drawBoard(boardString, shadowString, "", option, turn, command)
		elif command == "exit":
			board.quit()
			stockfish.engine.kill()
			break
	
	sys.exit()

class Board(Frame):

	def __init__(self, parent):
		Frame.__init__(self, parent)
		self.parent = parent
		self.initUI()

	def quit(self):
		self.parent.destroy()

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
		self.drawBoard(boardString, shadowString, "", "", "w", "move")
		

	def centerWindow(self):
		boardWidth = 320 # left side (56) + 8(26) + right side (56)
		boardHeight = 208

		screenWidth = self.parent.winfo_screenwidth()
		screnHeight = self.parent.winfo_screenheight()
		centerWidth = (screenWidth)/2
		centerHeight =(screnHeight)/2

		self.parent.geometry('%dx%d+%d+%d' % (boardWidth, boardHeight, 
											  0, 0))

	def drawBoard(self, boardString, shadowString, hint, option, turn, command):
		isWhite = True
		sidePanelWidth = 56
		squareWidth = 26
		squareHeight = 26
		topX = sidePanelWidth
		topY = 0
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
		
		optionRow = -1
		optionColumn = -1
		if option:
			optionRow = 7 - (ord(option[0]) - ord('0'))
			optionColumn = ord(option[1]) - ord('0')

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
				if col == optionColumn and row == optionRow:
					border = "#ff0"
					interior = "#ff0"
				self.canvas.create_rectangle(
							(topX + (squareWidth*col)),
							(topY + (squareHeight*row)),
							(topX + (squareWidth*col) + squareWidth),
							(topY + (squareHeight*row) + squareHeight),
							outline=border, fill=interior)
				if pieceName != '.':
					self.canvas.create_image(
							topX + 13 + 26*col, 
							topY + 13 + 26*row, 
							image=self.pieces[pieceName])
				isWhite = not isWhite
					
			isWhite = not isWhite
		
		if command == "error" :
			sidePanelColor = "#f00"
		elif command == "hint":
			sidePanelColor = "#ff0"
		else :
			sidePanelColor = "#0f0"
		
		if turn == 'w':
			self.canvas.create_rectangle(0,0,sidePanelWidth,208,fill=sidePanelColor)
			self.canvas.create_rectangle(sidePanelWidth+8*squareWidth,0,
																   sidePanelWidth+8*squareWidth+sidePanelWidth,208,
																   fill="#333")
		else:
			self.canvas.create_rectangle(0,0,sidePanelWidth,208,fill="#333")
			self.canvas.create_rectangle(sidePanelWidth+8*squareWidth,0,
																   sidePanelWidth+8*squareWidth+sidePanelWidth,208,
																   fill=sidePanelColor)
		

def main():
	root= Tk()
	root.overrideredirect(1) # Remove title bar of window in GUI
	board = Board(root)
	chessUpdate = Thread(target = ChessUpdate, args = (board,))
	chessUpdate.start()
	root.mainloop()
	


if __name__ == '__main__':
	main()	
