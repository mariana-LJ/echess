import subprocess

class Stockfish:
	def __init__(self):
		self.engine = subprocess.Popen(
			'./stockfish',
			universal_newlines=True,
			stdin=subprocess.PIPE,
			stdout=subprocess.PIPE,)
		self.waitForLine("Stockfish")
		self.writeLine("uci")
		self.waitForLine("uciok")
		self.writeLine("setoption name Hash value 32")
		self.writeLine("isready")
		self.waitForLine("readyok")

	def waitForLine(self, prefix):
		line = self.engine.stdout.readline().strip()
		while not line.startswith(prefix):
			line = self.engine.stdout.readline().strip()
		return line

	def writeLine(self, line):
		self.engine.stdin.write(line+'\n')

	def analyze(self, fen):
		self.writeLine("ucinewgame");
		self.writeLine("position fen " + fen);
		self.writeLine("go movetime " + str(3000)); # 3 seconds
		line = self.waitForLine("bestmove");
		# promotion not implemented
		return line[len("bestmove "):len("bestmove ")+4]
