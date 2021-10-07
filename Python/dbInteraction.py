
def auth(cursor, login, password):
    cursor.execute("SELECT login, password FROM user")
    for row in cursor.fetchall():
        if row[0] == login and row[1] == password:
            return True
    return False
