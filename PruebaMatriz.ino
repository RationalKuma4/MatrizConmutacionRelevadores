/*//Abonado 1
#define S11 22	// numero
#define S12 23	// numero
#define S13 24	// estado peticion
#define S14 25	// salida

//Abonado 2
#define S21 28
#define S22 29
#define S23 30
#define S24 31

//Abonado 3
#define S31 34
#define S32 35
#define S33 36
#define S34 37

//Abonado 4
#define S41 40
#define S42 41
#define S43 42
#define S44 43

// Reles
#define R1 2
#define R2 4
#define R3 7
#define R4 8

int s11, s12, s13, s14;
int s21, s22, s23, s24;
int s31, s32, s33, s34;
int s41, s42, s43, s44;

struct Abonado
{
	String numero;
	int numeroSalida;
	int estadoMarcado;
	int rele;
};

Abonado abonados[4];

void SetPinsMode();
void ReadPins();
void CreaAbonados();
Abonado BucarAbonado(String numeroMarcado);
void Conmutar(Abonado abonadoDestino, Abonado abonadoOrigen);
void Liberar();

void setup()
{
	SetPinsMode();
	digitalWrite(R1, HIGH);
	digitalWrite(R2, HIGH);
	digitalWrite(R3, HIGH);
	digitalWrite(R4, HIGH);

	Serial.begin(9600);
}

void loop()
{
	delay(2000);
	ReadPins();
	CreaAbonados();

	String numMarc;
	Abonado encontrado, origen;

	if (s13 == 1)
	{
		numMarc = String(s11) + String(s12);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("00");
		Conmutar(encontrado, origen);
	}
	else if (s23 == 1)
	{
		numMarc = String(s21) + String(s22);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("01");
		Conmutar(encontrado, origen);
	}
	else if (s33 == 1)
	{
		numMarc = String(s31) + String(s32);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("10");
		Conmutar(encontrado, origen);
	}
	else if (s43 == 1)
	{
		numMarc = String(s41) + String(s42);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("11");
		Conmutar(encontrado, origen);
	}
	else
	{
		Liberar();
	}

	/*else if (s13 == 0)
	{
	numMarc = String(s11) + String(s12);
	auto encontrado = BucarAbonado(numMarc);
	auto origen = BucarAbonado("00");
	Liberar(encontrado, origen);
	}

	if (s23 == 1)
	{
		numMarc = String(s21) + String(s22);
		auto encontrado = BucarAbonado(numMarc);
		auto origen = BucarAbonado("01");
		Conmutar(encontrado, origen);
	}
	else if (s23 == 0)
	{
		numMarc = String(s21) + String(s22);
		auto encontrado = BucarAbonado(numMarc);
		auto origen = BucarAbonado("01");
		Liberar(encontrado, origen);
	}


	else if (s33 == 0)
	{
		numMarc = String(s31) + String(s32);
		auto encontrado = BucarAbonado(numMarc);
		auto origen = BucarAbonado("10");
		Liberar(encontrado, origen);
	}


	else if (s43 == 0)
	{
		numMarc = String(s41) + String(s42);
		auto encontrado = BucarAbonado(numMarc);
		auto origen = BucarAbonado("11");
		Liberar(encontrado, origen);
	}*/
}

void SetPinsMode()
{
	pinMode(S11, INPUT);
	pinMode(S12, INPUT);
	pinMode(S13, INPUT);
	pinMode(S14, OUTPUT);

	pinMode(S21, INPUT);
	pinMode(S22, INPUT);
	pinMode(S23, INPUT);
	pinMode(S24, OUTPUT);

	pinMode(S31, INPUT);
	pinMode(S32, INPUT);
	pinMode(S33, INPUT);
	pinMode(S34, OUTPUT);

	pinMode(S41, INPUT);
	pinMode(S42, INPUT);
	pinMode(S43, INPUT);
	pinMode(S44, OUTPUT);

	pinMode(R1, OUTPUT);
	pinMode(R2, OUTPUT);
	pinMode(R3, OUTPUT);
	pinMode(R4, OUTPUT);
}

void ReadPins()
{
	s11 = digitalRead(S11);
	s12 = digitalRead(S12);
	s13 = digitalRead(S13);

	s21 = digitalRead(S21);
	s22 = digitalRead(S22);
	s23 = digitalRead(S23);

	s31 = digitalRead(S31);
	s32 = digitalRead(S32);
	s33 = digitalRead(S33);

	s41 = digitalRead(S41);
	s42 = digitalRead(S42);
	s43 = digitalRead(S43);
}

void CreaAbonados()
{
	Abonado abonadoUno = { "00", S14, s13, R1 },
		abonadoDos = { "01", S24, s23, R2 },
		abonadoTres = { "10", S34, s33, R3 },
		abonadoCuatro = { "11", S44, s43, R4 };

	abonados[0] = abonadoUno;
	abonados[1] = abonadoDos;
	abonados[2] = abonadoTres;
	abonados[3] = abonadoCuatro;
}

Abonado BucarAbonado(String numeroMarcado)
{
	struct Abonado abonado = { "N",0,0,0 };
	for (auto i = 0; i < 4; ++i)
	{
		if (numeroMarcado.equals(abonados[i].numero))
		{
			abonado = abonados[i];
			break;
		}
	}
	return abonado;
}

void Conmutar(Abonado abonadoDestino, Abonado abonadoOrigen)
{
	if (!abonadoDestino.numero.equals("N"))
	{
		Serial.println("Abonado origen");
		Serial.println(abonadoOrigen.numero);
		Serial.println(abonadoOrigen.numeroSalida);
		Serial.println(abonadoOrigen.estadoMarcado);
		Serial.println(abonadoOrigen.rele);

		Serial.println();

		Serial.println(abonadoDestino.numero);
		Serial.println(abonadoDestino.numeroSalida);
		Serial.println(abonadoDestino.estadoMarcado);
		Serial.println(abonadoDestino.rele);

		digitalWrite(abonadoOrigen.numeroSalida, HIGH);
		digitalWrite(abonadoDestino.numeroSalida, HIGH);

		digitalWrite(abonadoOrigen.rele, LOW);
		digitalWrite(abonadoDestino.rele, LOW);
		delay(2000);
	}
}

void Liberar(Abonado abonadoDestino, Abonado abonadoOrigen)
{
	if (!abonadoDestino.numero.equals("N"))
	{
		/*Serial.println("Abonado origen");
		Serial.println(abonadoOrigen.numero);
		Serial.println(abonadoOrigen.numeroSalida);
		Serial.println(abonadoOrigen.estadoMarcado);
		Serial.println(abonadoOrigen.rele);

		Serial.println();

		Serial.println(abonadoDestino.numero);
		Serial.println(abonadoDestino.numeroSalida);
		Serial.println(abonadoDestino.estadoMarcado);
		Serial.println(abonadoDestino.rele);

		digitalWrite(abonadoOrigen.numeroSalida, LOW);
		digitalWrite(abonadoDestino.numeroSalida, LOW);

		digitalWrite(abonadoOrigen.rele, HIGH);
		digitalWrite(abonadoDestino.rele, HIGH);*/
	}
	digitalWrite(S14, LOW);
	digitalWrite(S24, LOW);
	digitalWrite(S34, LOW);
	digitalWrite(S44, LOW);

	digitalWrite(R1, HIGH);
	digitalWrite(R2, HIGH);
	digitalWrite(R3, HIGH);
	digitalWrite(R4, HIGH);
}*/

/*
int relay0 = 2;
int relay1 = 4;
int relay2 = 7;
int relay3 = 8;


void setup()
{
	// Configuración
	pinMode(relay0, OUTPUT); // Configurar relay como salida o OUTPUT
	pinMode(relay1, OUTPUT);
	pinMode(relay2, OUTPUT);
	pinMode(relay3, OUTPUT);
	Serial.begin(9600); // Abrir el puerto serie a la velocidad de 9600bps para trasnmicion de datos.
}

void loop()
{
	// Código principal donde ocurren en loop
	digitalWrite(relay0, HIGH); // envia señal alta al relay
	digitalWrite(relay1, HIGH);
	digitalWrite(relay2, HIGH);
	digitalWrite(relay3, HIGH);
	Serial.println("Relay accionado");
	delay(2000);           // 1 segundo

	digitalWrite(relay0, LOW);
	digitalWrite(relay1, LOW);
	digitalWrite(relay2, LOW);
	digitalWrite(relay3, LOW);
	Serial.println("Relay no accionado");
	delay(2000);           // 1 segundo

}*/

//Abonado 1
#define S11 22	// numero
#define S12 24	// numero
#define S13 26	// numero
#define S14 28	// estado peticion
#define S15 30	// salida

//Abonado 2
#define S21 32
#define S22 34
#define S23 36
#define S24 38
#define S25 40	// salida

//Abonado 3
#define S31 42
#define S32 44
#define S33 46
#define S34 48
#define S35 50

//Abonado 4
#define S41 23
#define S42 25
#define S43 27
#define S44 29
#define S45 31

//Abonado 5
#define S51 33
#define S52 35
#define S53 37
#define S54 39
#define S55 41

//Abonado 6
#define S61 43
#define S62 45
#define S63 47
#define S64 49
#define S65 51

// Reles
#define R1 2
#define R2 4
#define R3 7
#define R4 8
#define R5 8
#define R6 8

int s11, s12, s13, s14, s15;
int s21, s22, s23, s24, s25;
int s31, s32, s33, s34, s35;
int s41, s42, s43, s44, s45;
int s51, s52, s53, s54, s55;
int s61, s62, s63, s64, s65;

struct Abonado
{
	String numero;
	int numeroSalida;
	int estadoMarcado;
	int rele;
};

Abonado abonados[6];

void SetPinsMode();
void ReadPins();
void CreaAbonados();
Abonado BucarAbonado(String numeroMarcado);
void Conmutar(Abonado abonadoDestino, Abonado abonadoOrigen);
void Liberar();

void setup()
{
	SetPinsMode();
	digitalWrite(R1, HIGH);
	digitalWrite(R2, HIGH);
	digitalWrite(R3, HIGH);
	digitalWrite(R4, HIGH);
	digitalWrite(R5, HIGH);
	digitalWrite(R6, HIGH);
	Serial.begin(9600);
}

// Add the main program code into the continuous loop() function
void loop()
{
	delay(2000);
	ReadPins();
	CreaAbonados();

	String numMarc;
	Abonado encontrado, origen;

	if (s14 == 1)
	{
		numMarc = String(s11) + String(s12) + String(s13);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("001");
		Conmutar(encontrado, origen);
	}
	else if (s24 == 1)
	{
		numMarc = String(s21) + String(s22) + String(s23);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("010");
		Conmutar(encontrado, origen);
	}
	else if (s34 == 1)
	{
		numMarc = String(s31) + String(s32) + String(s33);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("011");
		Conmutar(encontrado, origen);
	}
	else if (s44 == 1)
	{
		numMarc = String(s41) + String(s42) + String(s43);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("100");
		Conmutar(encontrado, origen);
	}
	else if (s54 == 1)
	{
		numMarc = String(s51) + String(s52) + String(s53);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("101");
		Conmutar(encontrado, origen);
	}
	else if (s64 == 1)
	{
		numMarc = String(s61) + String(s62) + String(s63);
		encontrado = BucarAbonado(numMarc);
		origen = BucarAbonado("110");
		Conmutar(encontrado, origen);
	}
	else
	{
		Liberar();
	}
}

void SetPinsMode()
{
	pinMode(S11, INPUT);
	pinMode(S12, INPUT);
	pinMode(S13, INPUT);
	pinMode(S14, INPUT);
	pinMode(S15, OUTPUT);

	pinMode(S21, INPUT);
	pinMode(S22, INPUT);
	pinMode(S23, INPUT);
	pinMode(S24, INPUT);
	pinMode(S25, OUTPUT);

	pinMode(S31, INPUT);
	pinMode(S32, INPUT);
	pinMode(S33, INPUT);
	pinMode(S34, INPUT);
	pinMode(S35, OUTPUT);

	pinMode(S41, INPUT);
	pinMode(S42, INPUT);
	pinMode(S43, INPUT);
	pinMode(S44, INPUT);
	pinMode(S45, OUTPUT);

	pinMode(S51, INPUT);
	pinMode(S52, INPUT);
	pinMode(S53, INPUT);
	pinMode(S54, INPUT);
	pinMode(S55, OUTPUT);

	pinMode(S61, INPUT);
	pinMode(S62, INPUT);
	pinMode(S63, INPUT);
	pinMode(S64, INPUT);
	pinMode(S65, OUTPUT);

	pinMode(R1, OUTPUT);
	pinMode(R2, OUTPUT);
	pinMode(R3, OUTPUT);
	pinMode(R4, OUTPUT);
	pinMode(R5, OUTPUT);
	pinMode(R6, OUTPUT);
}

void ReadPins()
{
	s11 = digitalRead(S11);
	s12 = digitalRead(S12);
	s13 = digitalRead(S13);
	s14 = digitalRead(S14);

	s21 = digitalRead(S21);
	s22 = digitalRead(S22);
	s23 = digitalRead(S23);
	s24 = digitalRead(S24);

	s31 = digitalRead(S31);
	s32 = digitalRead(S32);
	s33 = digitalRead(S33);
	s34 = digitalRead(S34);

	s41 = digitalRead(S41);
	s42 = digitalRead(S42);
	s43 = digitalRead(S43);
	s44 = digitalRead(S44);

	s51 = digitalRead(S51);
	s52 = digitalRead(S52);
	s53 = digitalRead(S53);
	s54 = digitalRead(S54);

	s61 = digitalRead(S61);
	s62 = digitalRead(S62);
	s63 = digitalRead(S63);
	s64 = digitalRead(S64);
}

void CreaAbonados()
{
	Abonado abonadoUno = { "001", S14, s13, R1 },
		abonadoDos = { "010", S24, s23, R2 },
		abonadoTres = { "011", S34, s33, R3 },
		abonadoCuatro = { "100", S44, s43, R4 },
		abonadoCinco = { "101", S54, s53, R5 },
		abonadoSeis = { "110", S64, s63, R6 };

	abonados[0] = abonadoUno;
	abonados[1] = abonadoDos;
	abonados[2] = abonadoTres;
	abonados[3] = abonadoCuatro;
	abonados[4] = abonadoCinco;
	abonados[5] = abonadoSeis;
}

Abonado BucarAbonado(String numeroMarcado)
{
	struct Abonado abonado = { "N",0,0,0 };
	for (auto i = 0; i < 6; ++i)
	{
		if (numeroMarcado.equals(abonados[i].numero))
		{
			abonado = abonados[i];
			break;
		}
	}
	return abonado;
}

void Conmutar(Abonado abonadoDestino, Abonado abonadoOrigen)
{
	if (!abonadoDestino.numero.equals("N"))
	{
		digitalWrite(abonadoOrigen.numeroSalida, HIGH);
		digitalWrite(abonadoDestino.numeroSalida, HIGH);

		digitalWrite(abonadoOrigen.rele, LOW);
		digitalWrite(abonadoDestino.rele, LOW);
		delay(2000);
	}
}

void Liberar()
{
	digitalWrite(S14, LOW);
	digitalWrite(S24, LOW);
	digitalWrite(S34, LOW);
	digitalWrite(S44, LOW);
	digitalWrite(S54, LOW);
	digitalWrite(S64, LOW);

	digitalWrite(R1, HIGH);
	digitalWrite(R2, HIGH);
	digitalWrite(R3, HIGH);
	digitalWrite(R4, HIGH);
	digitalWrite(R5, HIGH);
	digitalWrite(R6, HIGH);
}

