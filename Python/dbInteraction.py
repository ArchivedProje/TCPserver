
def auth(cursor, login, password):
    cursor.execute("SELECT login, password FROM user")
    for row in cursor.fetchall():
        if row[0] == login and row[1] == password:
            return True
    return False


def set_connected(cursor, login):
    cursor.execute("UPDATE user SET status='connected' WHERE login='" + str(login) + "'")


def set_disconnected(cursor, login):
    cursor.execute("UPDATE user SET status='disconnected' WHERE login='" + str(login) + "'")


def get_users(cursor, login):
    cursor.execute("SELECT login, status FROM user")
    res = str()
    for row in cursor.fetchall():
        if row[0] != login:
            res += row[0] + ',' + row[1] + '\n'
    return res
