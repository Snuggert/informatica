import os
def build_response_header(content):
    return '''Content-Type: text/html; encoding=utf8
                Content-Length: %d
                Connection': close''' % len(content)

if __name__ == '__main__':
    table_content = '''
    '''
    for key, value in os.environ.items():
        table_content += '''
                            <tr>
                                <td>%s</td>
                                <td>%s</td>
                            </tr>''' % (key, value)
    content = '''
            <!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
            <html>
                <head>
                    <title>Environment</title>
                </head>
                <body>
                    <h1>Environment of Abeche</h1>    
                    <table border="1">
                        <tr>
                            <th>KEY</th>
                            <th>VALUE</th>
                        </tr>
                            %s
                        </table> 

                </body>
            </html>''' % (table_content)
    
    print(build_response_header(content))
    print('\n')
    print(content)