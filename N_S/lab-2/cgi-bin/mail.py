import os
if __name__ == '__main__':
	env = os.environ
	print(env['QUERY_STRING'])
