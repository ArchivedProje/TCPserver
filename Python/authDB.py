from base64 import b64decode


def get_auth_data():
    cfg_file = open('Python/Settings/authData.cfg', 'r')
    data = list()
    for line in cfg_file:
        if line not in ['\n']:
            data.append(line)
    cfg_file.close()
    return b64decode(data[0].encode("UTF-8")).decode("UTF-8"), b64decode(data[1].encode("UTF-8")).decode("UTF-8")
