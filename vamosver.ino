#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SD.h>
#include <SPI.h>

#define conta_tam 8
#define pass_tamanho 5
#define levantar 4

int MotorPin1 = 35;
int MotorPin2 = 36;
int MotorPin3 = 37;
int MotorPin4 = 38;
int MotorPin5 = 39;
int MotorPin6 = 40;

int inicio = 0;
int verif_welcome, verif_login = 0;
int check_user = 0;
int check_usero = 0;
int check_log;
int check_dl, check_lev, check_levantament;
int check_n10, check_n20, check_n50, check_n100 = 0;
int check_salders = 0;
int n_notas_10[0], n_notas_20[0], n_notas_50[0];
int n10 = 0; int n20 = 0; int n50 = 0;
File myFile;
char loggers[0];
char boggers[0];
String numero_conta;
int saldoo = 0;
String a10 = "";
String a20 = "";
String a50 = "";
int salde = 0;
int levanta = 0;
int lev10, lev20, lev50 = 0;

char Conta_intro[conta_tam];
byte intro_count = 0;
byte main_count = 0;

char Data[pass_tamanho];
byte data_count = 0;
bool Pass_is_good;
char customKey;

char Levantaje[levantar];
int levanta_count = 0;
//---------------------------------------------------------
//---------------------------------------------------------
//programa keypad------------------------------------------
const byte linhas = 4;
const byte colunas = 3;
const int RS = A0, E = A1, D4 = A2, D5 = A3, D6 = A4, D7 = A5;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);


char teclado[linhas][colunas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte linhaPins[linhas] = {28, 27, 26, 25};
byte colunaPins[colunas] = {24, 23, 22};

Keypad Keypadezao = Keypad(makeKeymap(teclado), linhaPins, colunaPins, linhas, colunas);
//-------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  while (!Serial) {
    ;  //wait until its connected
  }
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorPin3, OUTPUT);
  pinMode(MotorPin4, OUTPUT);
  pinMode(MotorPin5, OUTPUT);
  pinMode(MotorPin6, OUTPUT);

  Serial.print("A inicilizar o SD card. . .");
  if (!SD.begin(53)) {      //Isto abre a comunicacao do pin 53 (CS) que se nao estiver conectado com o arduino, da erro
    Serial.println("Inicializacao Falhada!");
    return;
  }
  // No aso de ser sucedido, aparece esta mensagem abaixo
  Serial.println("Inicializacao Concluida.");

  Serial.println("A criar clientes.txt. . ." );
  myFile = SD.open("clientes.txt", FILE_WRITE);  //Lista_de_Clientes.txt e o nome do ficheiro a ser criado e FILE_WRITE e o comando para o criar
  myFile.close();  //Fecho do ficheiro

  if (SD.exists("clientes.txt")) { // Se o ficheiro Lista_de_Clentes existir.
    Serial.println("clientes.txt existe.");
  } else { // And if not
    Serial.println("clientes.txt nao existe.");
  }
}
//-------------------------------------------------------------------------

void CriarConta(char Data[]) {
  Serial.begin(9600); //to open the serial communication
  while (!Serial) {
    ;  //wait until its connected
  }

  Serial.print("A inicilizar o SD card. . .");
  if (!SD.begin(53)) {      //Isto abre a comunicacao do pin 4 (CS) que se nao estiver conectado com o arduino, da erro
    Serial.println("Inicializacao Falhada!");
    return;
  }
  // No aso de ser sucedido, aparece esta mensagem abaixo
  Serial.println("Inicializacao Concluida.");

  Serial.println("A criar clientes.txt. . ." );
  myFile = SD.open("clientes.txt", FILE_WRITE);  //Lista_de_Clientes.txt e o nome do ficheiro a ser criado e FILE_WRITE e o comando para o criar

  if (SD.exists("clientes.txt")) { // Se o ficheiro Lista_de_Clentes existir.
    Serial.println("clientes.txt existe.");
  } else { // And if not
    Serial.println("clientes.txt nao existe.");
  }


  if (myFile) {
    Serial.print("A escrever em clientes.txt...");

    for (int i = 0; i < 7; i++)
    {
      myFile.print(Data[i]);
    }
    myFile.println(" ");
    myFile.close(); // Close the file after opening
    Serial.println("LESSSS GOOOOOOO."); //Display this if the file was successfully written.
  }
  else { // And if not display error message.
    Serial.println("Erro ao abrir clientes.txt");
  }

}


//Função que apaga o utilizador e a pass da tabela introduzida---------
void clearData() {
  while (data_count != 0 || intro_count != 0) {
    Data[data_count--] = 0;
    //Conta_intro[intro_count--] = 0;

  }
  return;
}

void clearConta() {
  while (intro_count != 0) {
    //Data[data_count--] = 0;
    Conta_intro[intro_count--] = 0;

  }
  return;
}

//-------------------------------------------------------------------------

void(* resetFunc) (void) = 0;

//-------------------------------------------------------------------------

void VerificarConta(char Data[]) {
  myFile = SD.open("clientes.txt");
  Serial.println("aberto");
  while (myFile.available()) {
    unsigned long lolers = (unsigned long)atol(Data);
    numero_conta = myFile.readStringUntil('\n');
    Serial.println(numero_conta); //Printing for debugging purpose
    Serial.println(Data);
    Serial.println(lolers);
    if (numero_conta.toInt() == lolers) { // checking integer
      Serial.println("found");
      Serial.println("Match!");
      Serial.println("sugoi");
      check_user = 1;
    }
  }
}


//-------------------------------------------------------------------------

void VerificarPass(char Data[], String ncontas) {
  myFile = SD.open(ncontas);
  Serial.println("aberto");
  while (myFile.available()) {
    int lolers = atoi(Data);
    numero_conta = myFile.readStringUntil('\n');
    Serial.println(numero_conta); //Printing for debugging purpose
    Serial.println(Data);
    Serial.println(lolers);
    if (numero_conta.toInt() == lolers) { // checking integer
      Serial.println("found");
      Serial.println("Match!");
      lcd.clear();
      verif_login = 1;
      Serial.println("sugoi");
    }
  }
}

//-------------------------------------------------------------------------

bool verificar_saldo(int valor)
{
  String numsaldo = String(Conta_intro);
  numsaldo += String("9.txt"); //9 é o indicativo de saldo
  myFile = SD.open(numsaldo);
  if (myFile)
  {
    String pog = myFile.readString();
    salde = pog.toInt();
  }

  if (salde - valor < 0)
    return false;
  else
    return true;
}

//-------------------------------------------------------------------------

void numero_levantado(int valor)
{
  do {
    if (valor - 50 >= 0)
    {
      lev50++;
      valor = valor - 50;
    }
    if (valor - 20 >= 0)
    {
      lev20++;
      valor = valor - 20;
    }
    if (valor - 10 >= 0)
    {
      lev10++;
      valor = valor - 10;
    }
  } while (valor != 0);
}

//login--------------------------------------------------------------------
bool loginn(char costumizado) {
  //numero de conta aqui ////////////////
  if (check_log == 0) {
    lcd.setCursor(0, 0);
    lcd.print("0 - LOGIN");
    lcd.setCursor(0, 1);
    lcd.print("2 - CRIAR CONTA");
    costumizado = Keypadezao.getKey();
    loggers[0] = costumizado;
    if (costumizado)
    {
      Serial.println(costumizado);
      if (loggers[0] == '0')
      { Serial.println("Ola");
        lcd.clear();
        check_log = 1;
      }

      if (loggers[0] == '2')
      { Serial.println("MC RAUL DE LANDA");
        lcd.clear();
        check_log = 2;
      }
    }
  }

  //CASO DE DAR LOGIN NUMA CONTA JA EXISTENTE
  if (check_log == 1) {
    if (check_user == 0) {
      char costumizadooo;
      costumizadooo = Keypadezao.getKey();
      lcd.setCursor(0, 0);
      lcd.print("Numero de conta: ");
      while (costumizadooo == NO_KEY) costumizadooo = Keypadezao.getKey();

      if (costumizadooo) {
        Serial.println("Damir Gostosao");
        Conta_intro[intro_count] = costumizadooo;
        lcd.setCursor(intro_count, 1);
        lcd.print(costumizadooo);
        Serial.println(costumizadooo);
        intro_count++;
        Serial.println(intro_count);
      }

      if (intro_count == conta_tam - 1) {
        Serial.println("Pedro Boiolao");
        lcd.clear();
        VerificarConta(Conta_intro);
        if (check_user == 0) {
          lcd.print("Nao Existe");
          delay(2000);
          intro_count = 0;
        }
      }
    }
    Serial.println("Burro");

    //password aqui/////////
    if (check_user == 1) {

      char acostumizado;
      acostumizado = Keypadezao.getKey();
      lcd.setCursor(0, 0);
      lcd.print("Pass: ");
      while (acostumizado == NO_KEY) acostumizado = Keypadezao.getKey();

      if (acostumizado) {

        Data[data_count] = acostumizado;
        lcd.setCursor(data_count, 1);
        lcd.print("*");
        data_count++;
      }

      if (data_count == pass_tamanho - 1) {
        lcd.clear();
        String numconta = String(Conta_intro);
        numconta += String(".txt");
        VerificarPass(Data, numconta);
        if (verif_login == 1) {
          lcd.clear();
          delay(3000);
          return true;
        }
        else {
          lcd.print("Incorrect");
          delay(1000);
        }
      }
    }
  }
  //Isto no caso de querer criar conta
  //-----------------------------------------------------------

  if (check_log == 2) {
    if (check_usero == 0) {

      char costumizadoo;
      costumizadoo = Keypadezao.getKey();
      lcd.setCursor(0, 0);
      lcd.print("Numero de conta: ");
      while (costumizadoo == NO_KEY) costumizadoo = Keypadezao.getKey();

      if (costumizadoo) {
        Serial.println("Damir Gostosao");
        Conta_intro[intro_count] = costumizadoo;
        lcd.setCursor(intro_count, 1);
        lcd.print(costumizadoo);
        Serial.println(costumizadoo);
        intro_count++;
      }

      if (intro_count == conta_tam - 1) {
        Serial.println("Pedro Boiolao");
        lcd.clear();
        CriarConta(Conta_intro);
        delay(1000);
        check_usero = 1;
        lcd.clear();
      }
      Serial.println("Burrr");
    }
    //password aqui/////////
    if (check_usero == 1) {
      char costumizad;
      costumizad = Keypadezao.getKey();
      lcd.setCursor(0, 0);
      lcd.print("Pass: ");
      while (costumizad == NO_KEY) costumizad = Keypadezao.getKey();


      if (costumizad) {
        Serial.println("Hey");
        Data[data_count] = costumizad;
        lcd.setCursor(data_count, 1);
        lcd.print("*");
        data_count = data_count + 1;
      }


      if (data_count == pass_tamanho - 1) {
        lcd.clear();
        String numconta = String(Conta_intro);
        numconta += String(".txt");
        myFile = SD.open(numconta, FILE_WRITE);
        if (myFile)
        {
          Serial.print("A escrever em numcontas.txt...");

          for (int i = 0; i < 4; i++)
          {
            myFile.print(Data[i]);
          }
          myFile.println(" ");
          myFile.close(); // Close the file after opening
          Serial.println("LESSSS GOOOOOOO 2.0"); //Display this if the file was successfully written.
          verif_login = 2;
          lcd.clear();
          delay(5000);
          return true;
        }
        else { // And if not display error message.
          Serial.println("Erro ao abrir clientes.txt");
        }
      }
    }
  }
}

//tela inicial -------------------------------------------------------------
void welcome()
{
  lcd.clear();
  lcd.setCursor(2, 0);

  lcd.print("Bem-vindo ao");
  lcd.setCursor(3, 1);
  lcd.print("Banco Volt");
  delay(3000);
  lcd.clear();

  verif_welcome = 1;

}

//-------------------------------------------------------------------------

int num_notas(char costumizadex)
{
  boggers[0] = costumizadex;
  int piggers = atoi(boggers);
  Serial.println(piggers);
  lcd.setCursor(14, 1);
  lcd.print(costumizadex);
  if (piggers > -1 && piggers < 10)
  {
    return piggers;
  }
  else return 0;
}

//-------------------------------------------------------------------------
void elimina_conta(String lolew) {
  lolew = lolew + ".txt";
  SD.remove(lolew);
  return ;
}

//-------------------------------------------------------------------------

void deposito_solo(char costumizadex, char Conta_intro[])
{
  if (check_n10 == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("Num notas de 5");
    lcd.setCursor(0, 1);
    lcd.print("MAX(9 notas):");
    costumizadex = Keypadezao.getKey();
    if (costumizadex)
    {
      n_notas_10[0] = num_notas(costumizadex);
      Serial.println(n_notas_10[0]);
      n10 = n_notas_10[0];
      saldoo = (n10 * 5);
      Serial.print(saldoo);
      Serial.println(" saldo1");
      myFile = SD.open("notas10.txt");

      if (myFile)
      {
        Serial.println("notas10 pret pour la lecture");
        while (myFile.available())   // while CR/LF not detected ...
        {
          a10 = a10 + (char)myFile.read();
          Serial.println(a10);
          Serial.print(saldoo);
          Serial.println(" saldo1");
        }
        myFile.close();
      }

      a10 = a10 + n10;
      elimina_conta("notas10");

      myFile = SD.open("notas10.txt", FILE_WRITE);
      if (myFile)
      {
        Serial.print("A escrever em notas10.txt...");
        myFile.print(a10);
        myFile.close(); // Close the file after opening
      }
      else
        Serial.println("Dont work");

      lcd.clear();
      Serial.print(saldoo);
      Serial.println(" saldo1");
      check_n10 = 1;
      a10 = "";
    }
  }

  if (check_n10 == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("Num notas de 20");
    lcd.setCursor(0, 1);
    lcd.print("MAX(9 notas):");
    Serial.print(saldoo);
    Serial.println(" saldo1");
    costumizadex = Keypadezao.getKey();
    if (costumizadex)
    {
      n_notas_20[0] = num_notas(costumizadex);
      Serial.println(n_notas_20[0]);
      n20 = n_notas_20[0];
      saldoo = n10 * 5;
      saldoo = saldoo + (n20 * 20);
      Serial.print(saldoo);
      Serial.println(" saldo2");
      myFile = SD.open("notas20.txt");

      if (myFile)
      {
        Serial.println("notas20 pret pour la lecture");
        while (myFile.available())   // while CR/LF not detected ...
        {
          a20 = a20 + (char)myFile.read();
          Serial.println(a20);
        }
        myFile.close();
      }

      a20 = a20 + n20;
      String leite;
      elimina_conta(leite);

      myFile = SD.open("notas20.txt", FILE_WRITE);
      if (myFile)
      {
        Serial.print("A escrever em notas20.txt...");
        myFile.print(a20);
        myFile.close(); // Close the file after opening
      }
      else
        Serial.println("Dont work");
      lcd.clear();
      check_n20 = 1;
      check_n10 = 2;
      Serial.print(saldoo);
      Serial.println(" saldo10");
      a20 = "";
    }
  }

  if (check_n20 == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("Num notas de 50");
    lcd.setCursor(0, 1);
    lcd.print("MAX(9 notas):");
    costumizadex = Keypadezao.getKey();
    if (costumizadex)
    {
      n_notas_50[0] = num_notas(costumizadex);
      Serial.println(n_notas_50[0]);
      myFile = SD.open("notas50.txt");
      n50 = n_notas_50[0];
      saldoo = saldoo + ( n50 * 50);
      Serial.print(saldoo);
      Serial.println(" saldo3");
      if (myFile)
      {
        Serial.println("notas50 pret pour la lecture");
        while (myFile.available())   // while CR/LF not detected ...
        {
          a50 = a50 + (char)myFile.read();
          Serial.println(a50);
        }
        myFile.close();
      }

      myFile = SD.open("notas50.txt", FILE_WRITE);
      a50 = a50 + n50;
      elimina_conta("notas50");
      if (myFile)
      {
        Serial.print("A escrever em notas20.txt...");
        myFile.print(a50);
        myFile.close(); // Close the file after opening
      }
      else
        Serial.println("Dont work");
      lcd.clear();
      check_n50 = 1;
      check_n20 = 2;
      a50 = "";
    }
  }


  if (check_n50 == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("Tem 20s para ");
    lcd.setCursor(0, 1);
    lcd.print("colocar as notas");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tem 16s para ");
    lcd.setCursor(0, 1);
    lcd.print("colocar as notas");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tem 12s para ");
    lcd.setCursor(0, 1);
    lcd.print("colocar as notas");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tem 8s para ");
    lcd.setCursor(0, 1);
    lcd.print("colocar as notas");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tem 4s para ");
    lcd.setCursor(0, 1);
    lcd.print("colocar as notas");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tem 3s para ");
    lcd.setCursor(0, 1);
    lcd.print("colocar as notas");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tem 2s para ");
    lcd.setCursor(0, 1);
    lcd.print("colocar as notas");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tem 1s para ");
    lcd.setCursor(0, 1);
    lcd.print("colocar as notas");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Acabou o tempo");
    delay(2000);
    check_n50 = 2;
    check_salders = 1;
    lcd.clear();
    Serial.println(a10);
    Serial.println(a20);
    Serial.println(a50);
    lcd.setCursor(0, 0);
    lcd.print("Novo Saldo:");
    check_salders = 1;
    if (check_salders == 1)
    {
      lcd.setCursor(0, 1);
      lcd.print(saldoo);
      // VAI LINHA 330
      String numsaldo = String(Conta_intro);
      numsaldo += String("9.txt"); //9 é o indicativo de saldo
      myFile = SD.open(numsaldo, FILE_WRITE);
      if (myFile)
      {
        Serial.print("A escrever em numsaldo.txt...");
        myFile.print(saldoo);
        myFile.close(); // Close the file after opening
        delay(5000);
        resetFunc();
      }
      else
        Serial.println(" Dont work");
    }

  }
}
//-------------------------------------------------------------------------
bool deposito_levantamento(char costumizadex)
{
  if (check_dl == 0) {
    lcd.setCursor(0, 0);
    lcd.print("0 - DEPOSITO");
    lcd.setCursor(0, 1);
    lcd.print("2 - LEVANTAMENTO");
    costumizadex = Keypadezao.getKey();
    boggers[0] = costumizadex;
    if (costumizadex)
    {
      Serial.println(costumizadex);
      if (boggers[0] == '0')
      { Serial.println("HEY");
        lcd.clear();
        check_dl = 1;
      }

      if (boggers[0] == '2')
      { Serial.println("BABILONIA");
        lcd.clear();
        check_dl = 2;
      }
    }
    if (check_dl == 1)
    {
      if (check_n10 == 0)
      {
        lcd.setCursor(0, 0);
        lcd.print("Num notas de 5");
        lcd.setCursor(0, 1);
        lcd.print("MAX(9 notas):");
        costumizadex = Keypadezao.getKey();
        while (costumizadex == NO_KEY) costumizadex = Keypadezao.getKey();
        if (costumizadex)
        {
          n_notas_10[0] = num_notas(costumizadex);
          Serial.println(n_notas_10[0]);
          n10 = n_notas_10[0];
          saldoo = (n10 * 5);
          Serial.print(saldoo);
          Serial.println(" saldo1");
          myFile = SD.open("notas10.txt");

          if (myFile)
          {
            Serial.println("notas10 pret pour la lecture");
            while (myFile.available())   // while CR/LF not detected ...
            {
              String ok = myFile.readString();
              a10 = ok.toInt();
              Serial.println(a10);
              Serial.print(saldoo);
              Serial.println(" saldo1");
            }
            myFile.close();
          }

          a10 = a10 + n10;
          SD.remove("notas10.txt");

          myFile = SD.open("notas10.txt", FILE_WRITE);
          if (myFile)
          {
            Serial.print("A escrever em notas10.txt...");
            myFile.print(a10);
            myFile.close(); // Close the file after opening
          }
          else
            Serial.println("Dont work");

          lcd.clear();
          Serial.print(saldoo);
          Serial.println(" saldo1");
          check_n10 = 1;
          a10 = "";
        }
      }

      if (check_n10 == 1)
      {
        lcd.setCursor(0, 0);
        lcd.print("Num notas de 20");
        lcd.setCursor(0, 1);
        lcd.print("MAX(9 notas):");
        Serial.print(saldoo);
        Serial.println(" saldo1");
        costumizadex = Keypadezao.getKey();
        while (costumizadex == NO_KEY) costumizadex = Keypadezao.getKey();
        if (costumizadex)
        {
          n_notas_20[0] = num_notas(costumizadex);
          Serial.println(n_notas_20[0]);
          n20 = n_notas_20[0];
          saldoo = n10 * 5;
          saldoo = saldoo + (n20 * 20);
          Serial.print(saldoo);
          Serial.println(" saldo2");
          myFile = SD.open("notas20.txt");

          if (myFile)
          {
            Serial.println("notas20 pret pour la lecture");
            while (myFile.available())   // while CR/LF not detected ...
            {
              a20 = a20 + (char)myFile.read();
              Serial.println(a20);
            }
            myFile.close();
          }

          a20 = a20 + n20;
          SD.remove("notas20.txt");

          myFile = SD.open("notas20.txt", FILE_WRITE);
          if (myFile)
          {
            Serial.print("A escrever em notas20.txt...");
            myFile.print(a20);
            myFile.close(); // Close the file after opening
          }
          else
            Serial.println("Dont work");
          lcd.clear();
          check_n20 = 1;
          check_n10 = 2;
          Serial.print(saldoo);
          Serial.println(" saldo10");
          a20 = "";
        }
      }

      if (check_n20 == 1)
      {
        lcd.setCursor(0, 0);
        lcd.print("Num notas de 50");
        lcd.setCursor(0, 1);
        lcd.print("MAX(9 notas):");
        costumizadex = Keypadezao.getKey();
        while (costumizadex == NO_KEY) costumizadex = Keypadezao.getKey();
        if (costumizadex)
        {
          n_notas_50[0] = num_notas(costumizadex);
          Serial.println(n_notas_50[0]);
          myFile = SD.open("notas50.txt");
          n50 = n_notas_50[0];
          saldoo = saldoo + ( n50 * 50);
          Serial.print(saldoo);
          Serial.println(" saldo3");
          if (myFile)
          {
            Serial.println("notas50 pret pour la lecture");
            while (myFile.available())   // while CR/LF not detected ...
            {
              a50 = a50 + (char)myFile.read();
              Serial.println(a50);
            }
            myFile.close();
          }

          myFile = SD.open("notas50.txt", FILE_WRITE);
          a50 = a50 + n50;
          SD.remove("notas50.txt");
          if (myFile)
          {
            Serial.print("A escrever em notas20.txt...");
            myFile.print(a50);
            myFile.close(); // Close the file after opening
          }
          else
            Serial.println("Dont work");
          lcd.clear();
          check_n50 = 1;
          check_n20 = 2;
          a50 = "";
        }
      }


      if (check_n50 == 1)
      {
        lcd.setCursor(0, 0);
        lcd.print("Tem 20s para ");
        lcd.setCursor(0, 1);
        lcd.print("colocar as notas");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tem 16s para ");
        lcd.setCursor(0, 1);
        lcd.print("colocar as notas");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tem 12s para ");
        lcd.setCursor(0, 1);
        lcd.print("colocar as notas");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tem 8s para ");
        lcd.setCursor(0, 1);
        lcd.print("colocar as notas");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tem 4s para ");
        lcd.setCursor(0, 1);
        lcd.print("colocar as notas");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tem 3s para ");
        lcd.setCursor(0, 1);
        lcd.print("colocar as notas");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tem 2s para ");
        lcd.setCursor(0, 1);
        lcd.print("colocar as notas");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tem 1s para ");
        lcd.setCursor(0, 1);
        lcd.print("colocar as notas");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Acabou o tempo");
        delay(2000);
        check_n50 = 2;
        check_salders = 1;
        lcd.clear();
        Serial.println(a10);
        Serial.println(a20);
        Serial.println(a50);
        lcd.setCursor(0, 0);
        lcd.print("Novo Saldo:");
        check_salders = 1;
        if (check_salders == 1)
        {
          lcd.setCursor(0, 1);
          lcd.print(saldoo);
          // VAI LINHA 330
          String numsaldo = String(Conta_intro);
          numsaldo += String("9.txt"); //9 é o indicativo de saldo
          myFile = SD.open(numsaldo);
          if (myFile)
          {
            String pog = myFile.readString();
            salde = pog.toInt();
          }

          Serial.println(salde);
          saldoo = saldoo + salde;
          SD.remove(numsaldo);
          lcd.setCursor(0, 1);
          lcd.print(saldoo);

          myFile = SD.open(numsaldo, FILE_WRITE);
          if (myFile)
          {
            Serial.print("A escrever em numsaldo.txt...");
            myFile.print(saldoo);
            myFile.close(); // Close the file after opening
            delay(5000);
            resetFunc();
          }
          else
            Serial.println(" Dont work");
        }
      }

    }

    if (check_dl == 2)
    {
      lcd.clear();
      if (check_lev == 0)
      {
        if (check_n10 == 0)
        {
          lcd.setCursor(0, 0);
          lcd.print("Num notas de 5");
          lcd.setCursor(0, 1);
          lcd.print("MAX(9 notas):");
          costumizadex = Keypadezao.getKey();
          while (costumizadex == NO_KEY) costumizadex = Keypadezao.getKey();
          if (costumizadex)
          {
            n_notas_10[0] = num_notas(costumizadex);
            Serial.println(n_notas_10[0]);
            n10 = n_notas_10[0];
            saldoo = (n10 * 5);
            Serial.print(saldoo);
            Serial.println(" saldo1");
            myFile = SD.open("notas10.txt");

            if (myFile)
            {
              Serial.println("notas10 pret pour la lecture");
              while (myFile.available())   // while CR/LF not detected ...
              {
                String ok = myFile.readString();
                a10 = ok.toInt();
                Serial.println(a10);
                Serial.print(saldoo);
                Serial.println(" saldo1");
              }
              myFile.close();
            }

            a10 = a10 + n10;
            SD.remove("notas10.txt");

            myFile = SD.open("notas10.txt", FILE_WRITE);
            if (myFile)
            {
              Serial.print("A escrever em notas10.txt...");
              myFile.print(a10);
              myFile.close(); // Close the file after opening
            }
            else
              Serial.println("Dont work");

            lcd.clear();
            Serial.print(saldoo);
            Serial.println(" saldo1");
            check_n10 = 1;
            a10 = "";
          }
        }

        if (check_n10 == 1)
        {
          lcd.setCursor(0, 0);
          lcd.print("Num notas de 20");
          lcd.setCursor(0, 1);
          lcd.print("MAX(9 notas):");
          Serial.print(saldoo);
          Serial.println(" saldo1");
          costumizadex = Keypadezao.getKey();
          while (costumizadex == NO_KEY) costumizadex = Keypadezao.getKey();
          if (costumizadex)
          {
            n_notas_20[0] = num_notas(costumizadex);
            Serial.println(n_notas_20[0]);
            n20 = n_notas_20[0];
            saldoo = n10 * 5;
            saldoo = saldoo + (n20 * 20);
            Serial.print(saldoo);
            Serial.println(" saldo2");
            myFile = SD.open("notas20.txt");

            if (myFile)
            {
              Serial.println("notas20 pret pour la lecture");
              while (myFile.available())   // while CR/LF not detected ...
              {
                a20 = a20 + (char)myFile.read();
                Serial.println(a20);
              }
              myFile.close();
            }

            a20 = a20 + n20;
            SD.remove("notas20.txt");

            myFile = SD.open("notas20.txt", FILE_WRITE);
            if (myFile)
            {
              Serial.print("A escrever em notas20.txt...");
              myFile.print(a20);
              myFile.close(); // Close the file after opening
            }
            else
              Serial.println("Dont work");
            lcd.clear();
            check_n20 = 1;
            check_n10 = 2;
            Serial.print(saldoo);
            Serial.println(" saldo10");
            a20 = "";
          }
        }

        if (check_n20 == 1)
        {
          lcd.setCursor(0, 0);
          lcd.print("Num notas de 50");
          lcd.setCursor(0, 1);
          lcd.print("MAX(9 notas):");
          costumizadex = Keypadezao.getKey();
          while (costumizadex == NO_KEY) costumizadex = Keypadezao.getKey();
          if (costumizadex)
          {
            n_notas_50[0] = num_notas(costumizadex);
            Serial.println(n_notas_50[0]);
            myFile = SD.open("notas50.txt");
            n50 = n_notas_50[0];
            saldoo = saldoo + ( n50 * 50);
            Serial.print(saldoo);
            Serial.println(" saldo3");
            if (myFile)
            {
              Serial.println("notas50 pret pour la lecture");
              while (myFile.available())   // while CR/LF not detected ...
              {
                a50 = a50 + (char)myFile.read();
                Serial.println(a50);
              }
              myFile.close();
            }

            myFile = SD.open("notas50.txt", FILE_WRITE);
            a50 = a50 + n50;
            SD.remove("notas50.txt");
            if (myFile)
            {
              Serial.print("A escrever em notas20.txt...");
              myFile.print(a50);
              myFile.close(); // Close the file after opening
            }
            else
              Serial.println("Dont work");
            lcd.clear();
            check_n50 = 1;
            check_n20 = 2;
            a50 = "";
          }
        }
        String numsaldo = String(Conta_intro);
        numsaldo += String("9.txt"); //9 é o indicativo de saldo
        myFile = SD.open(numsaldo);
        if (myFile)
        {
          String pog = myFile.readString();
          salde = pog.toInt();
        }

        Serial.println(salde);
        SD.remove(numsaldo);
        lcd.setCursor(0, 1);
        lcd.print(salde - saldoo);
        saldoo = salde - saldoo;

        Serial.println("Pedro Boiolao");
        lcd.clear();
        check_levantament = 1;

        if (check_levantament = 1) {
          if (verificar_saldo(saldoo) == false)
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Incorreto");
            delay(2000);
          }
          else
          {
            myFile = SD.open(numsaldo, FILE_WRITE);
        if (myFile)
        {
          Serial.print("A escrever em numsaldo.txt...");
          myFile.print(saldoo);
          myFile.close(); // Close the file after opening

            unsigned long millis10 = millis();
            unsigned long millis20 = millis();
            unsigned long millis50 = millis();
            if(n10 != 0)
              {
                  digitalWrite(MotorPin1, 100);
                  digitalWrite(MotorPin2, 100);
                  delay(1000);
                  n10 = n10 - 1;
                }
                else{
                  digitalWrite(MotorPin1, LOW);
                  digitalWrite(MotorPin2, LOW);
                }

              if(n20 != 0)
              {
                  digitalWrite(MotorPin3, 100);
                  digitalWrite(MotorPin4, 100);
                  delay(1000);
                  n20 = n20 - 1;
                }
                else{
                  digitalWrite(MotorPin3, LOW);
                  digitalWrite(MotorPin4, LOW);
                }

              if(n50 != 0)
              {
                  digitalWrite(MotorPin5, 100);
                  digitalWrite(MotorPin6, 100);
                  delay(1000);
                  n50 = n50 - 1;
                  
              }
                else{
                  digitalWrite(MotorPin5, LOW);
                  digitalWrite(MotorPin6, LOW);
                }
             }
            else Serial.println("Dont Work");
          } 
        }
      }
      Serial.println("Leite");
      delay(5000);
      resetFunc();
    }
  }
}
//--------------------------------------------------------------------------


void loop() {
  char costumizado = Keypadezao.getKey();

  if (verif_welcome == 0) {
    digitalWrite(MotorPin1, LOW);
    digitalWrite(MotorPin2, LOW);
    digitalWrite(MotorPin3, LOW);
    digitalWrite(MotorPin4, LOW);
    digitalWrite(MotorPin5, LOW);
    digitalWrite(MotorPin6, LOW);
    welcome();
  }
  if (verif_login == 0)
  {
    loginn(costumizado);
  }
  if (verif_login == 1)
  {
    deposito_levantamento(costumizado);
  }
  if (verif_login == 2)
  {
    deposito_solo(costumizado, Conta_intro);
  }
}
