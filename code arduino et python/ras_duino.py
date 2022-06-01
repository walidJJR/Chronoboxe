# Importer les libraries qui simplifie le travail
import serial, time
import mysql.connector



# nom table : 'test'
# 4 Variables TEXTE:
# 'msg'
# 'a'
# 'b'
# 'c'
# Permet d'envoyer la requette
def send_my_sql(msg):
    sql = "INSERT INTO test (msg, a, b, c) VALUES (%s, %s, %s, %s)"
    val = (msg, "a","b","c")
    mycursor.execute(sql, val)

    my_data_base.commit()

    print("Envoye a la BD")


# Objet  Serial_arduino  qui lit sur le port /dev/ttyUSB0
class Serial_arduino():
    # Creation de la communication USB
    def __init__(self):
        #/dev/ttyUSB0
        #/COM3
        self.arduino = serial.Serial("/dev/ttyUSB0", 9600, timeout=1)
        time.sleep(0.1)  # wait for serial to open
        if self.arduino.isOpen():
            print("{} connected!".format(self.arduino.port))

    # Lecture sur le port
    def read_data(self):
        answer = self.arduino.readline()
        # Si le message est vide, ne rien faire
        if answer.decode().__len__() == 0:
            return
        # Si le message contiens '|' alors l'envoyer
        if answer.decode().__contains__("|"):
            send_my_sql(answer.decode().replace("|", ""))
        print(answer.decode().replace("|", ""))
        #if self.arduino.inWaiting() > 0:
            #answer = self.arduino.readline()
            #print(answer.decode(), answer.decode().__contains__("|"))
            #self.arduino.flushInput()
        #time.sleep(0.1)



comm = Serial_arduino()
time.sleep(2)

# Parametres de la connexion
my_data_base = mysql.connector.connect(
  host="localhost",
  user="pi",
  password="Wawa",
  database="Test_Boxe"
)
mycursor = my_data_base.cursor()

# Tout le temps, lire l'information
while 1:
    comm.read_data()