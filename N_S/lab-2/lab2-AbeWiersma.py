# Student name: Abe Wiersma
# Student number: 10433120\
# Institute: University of Amsterdam
# Course: Networking and System security
# 
# File: assignment 1 and 2 for lab2
# Date: 9-9-2013

import socket, os, sys, argparse, signal, sys, re, subprocess

responses = {200: 'OK', 404: 'Not Found', 501: 'Not Implemented'}

# handle SIGINT for smooth exit
def signal_handler(signal, frame):
    print '\nServer Closing.'
    server.close()
    sys.exit()

def get_file_type(location):
    try:
        return re.search('\.([^.]+)$', location).group(0)
    except NameError as e:
        return ''
    except AttributeError as e:
        return ''

def build_response_headers(filetype, content):
    if filetype == 'html':
        return '''Content-Type: text/html; encoding=utf8
                    Content-Length: %d
                    Connection': close''' % len(content)
    elif filetype == 'png':
            return'''Content-Type: image/x-png
                        Content-Length': %d
                        Connection': 'close''' % len(content)
    else:
        return ''

def build_response_status(response_proto='HTTP/1.1', response_number=200):
    response_status = str(response_number) + ' ' + responses[response_number]
    return '%s %s' % (response_proto, response_status)

def return_to_conn(conn, response_number, location='', content=''):
    if response_number == 404:
        content = '''
            <!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
            <html>
                <head>
                    <title>404 Not Found</title>
                </head>
                <body>
                    <h1>Not Found</h1>
                    <p>The requested URL %s was not found on this server.</p>
                    <hr>
                    <address>Abeche Server</address>
                </body>
            </html>''' % (location)

    # response protocol
    response_proto = 'HTTP/1.1'
    conn.send(build_response_status(response_proto, response_number))
    conn.send('\n')

    filetype = get_file_type(location)

    # send response headers
    conn.send(build_response_headers(filetype, content))
    conn.send('\n')
    conn.sendall(content)
    conn.close()

def serve(port, public_html, cgibin):
    signal.signal(signal.SIGINT, signal_handler)
    """
    The entry point of the HTTP server.
    port: The port to listen on.
    public_html: The directory where all static files are stored.
    cgibin: The directory where all CGI scripts are stored.
    """
    HOST = ''
    PORT = port
    global server 
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
    server.bind((HOST,PORT))
    server.listen(1)


    while 1:

        # connection to client and address to client
        conn, addr = server.accept()
        data = conn.recv(1024)
        if not data:
            continue

        # Use regex to find the type of request and location
        request_regex = re.search('([A-Z]{3,7}) (/.*)(?= ) (.*)', data)
        if not request_regex:
            return_to_conn(conn, 501)
            continue

        if not request_regex.group(1):
            return_to_conn(conn, 501)
            continue

        # set request type.
        request = request_regex.group(1)
        if request != 'GET':
            return_to_conn(conn, 501)
            continue

        if not request_regex.group(2):
            continue

        # set location.
        location = request_regex.group(2)
        location_regex = re.search('/cgi-bin(/.*)?', location)
        if location_regex:
            location_regex = re.search('/cgi-bin(/.*.py)',location)
            if not location_regex:
                return_to_conn(conn, 501)
                continue
            file_location = cgibin + location_regex.group(1)
            location_regex = re.search('.*\?(.*)', location)
            if not location_regex:
                query_string = ''
            else:
                query_string = location_regex.group(1)

            cmd = 'python ' + file_location
            print(cmd)

            conn.sendall(build_response_status())
            conn.sendall('\n')
            # try starting subprocess
            subprocess.Popen(cmd, shell=True, stdout=conn)

            conn.close()
            continue

        if(location == '/'):
            location = '/index.html'

        # set/check response_proto.
        if not request_regex.group(3):
            proto = request_regex.group(3)
            if proto != 'HTTP/1.1' or proto != 'CGI/1.1':
                response_status = '501 ' + responses[501]
                conn.send('%s %s' % (response_proto, response_status))
                conn.close()
                continue

        # logging.
        print('request for : ' + location + ' by: ', addr)

        # try and retrieve file requested.
        content = None
        try:
            content = open(public_html+location, 'rb')
            content = content.read()
        except IOError:
            print('File not found')
            return_to_conn(conn, 404, location)

        # if content return requested file in html format
        if content:
            return_to_conn(conn, 200, location, content)
            

## This the entry point of the script.
## Do not change this part.
if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('--port', help='port to bind to', default=8080, type=int)
    p.add_argument('--public_html', help='home directory', default='./public_html')
    p.add_argument('--cgibin', help='cgi-bin directory', default='./cgi-bin')
    args = p.parse_args(sys.argv[1:])
    public_html = os.path.posixpath(args.public_html)
    cgibin = os.path.abspath(args.cgibin)
    serve(args.port, public_html, cgibin)