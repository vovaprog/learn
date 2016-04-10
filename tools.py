
def create_empty_file(file_name):
    basedir = os.path.dirname(file_name)
    if not os.path.exists(basedir):
        os.makedirs(basedir)        
    open(file_name, 'a').close()

def replaceRegex(file_path, regexp, subst):
    fh, abs_path = tempfile.mkstemp()
    with open(abs_path,'w') as new_file:
        with open(file_path) as old_file:
            for line in old_file:
                new_line = re.sub(regexp,subst,line)
                new_file.write(new_line)
    os.close(fh)
    os.remove(file_path)
    shutil.move(abs_path, file_path)

