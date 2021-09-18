#include<stdio.h>
#include<windows.h>      /*Esta biblioteca incluye una función que permite dar posición al cursor*/ 
#include<conio.h>        /*Biblioteca que detecta teclas presionadas*/
#include<stdlib.h>       /*Biblioteca que incluye la función rand (azar)*/
#include<list>           /*Lo necesitamos para crear listas(para los escupitajos del pollo y las piedras)*/
using namespace std;     /*Se necesita para las listas*/



#define ARRIBA 72        /*Los numeros correponden a los valores de las teclas del teclado*/
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80


/*Función que situa el cursor en la posición(x,y)*/
void gotoxy(int x, int y){	
	HANDLE hCon;  /*Identificador de la consola en la que vamos a trabajar*/
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);  /*Recuperamos el identificador de la consola 
                                               al comenzar el programa, con parametro de STD_OUTPUT_HANDLE 
											   tenemos control a la salida de la consola*/
	COORD dwPos;  /*Coordenadas x,y*/
	dwPos.X = x;
	dwPos.Y = y;
	
	/*Función que pone el cursor en ciertas coordenadas, primer paramtero ID de la consola
     seguno paramtro posición del cursor (estructura predefinida en windows.h)*/
	SetConsoleCursorPosition(hCon, dwPos);
}


/*Oculta el cursor en la pantalla*/
void  ocultarCursor(){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci; /*Controlamos la apariencia del cursor de la pantalla*/
	cci.dwSize = 1;  /*Tamño del cursor*/
	cci.bVisible = FALSE;    /*Ocultamos el cursor*/
	/*Controlamos las características del cursor en la pantalla*/
	SetConsoleCursorInfo(hCon,&cci);  /*&cci se pasa por referencia para poder modificar sus datos*/
}


/*Función para delimitar el juego dentro de un cuadrado de la consola*/
void pintar_limites(){
	/*Limites horizonales2*/
	for(int i = 2; i<78 ; i++){
		gotoxy(i, 3);printf("%C", 205);     /*Línea superior*/
		gotoxy(i, 33);printf("%C", 205);    /*Línea inferior*/
	}
	/*Limites verticales*/
	for(int i = 4; i<33 ; i++){
		gotoxy(2, i);printf("%C", 186);     /*Línea izquierda*/
		gotoxy(77, i);printf("%C", 186);    /*Línea derecha*/
	}
	/*Dibujamos las esquinas*/
	gotoxy(2,3);printf("%c",201);
	gotoxy(2,33);printf("%c",200);
	gotoxy(77,3);printf("%c",187);
	gotoxy(77,33);printf("%c",188);
}

/* ************************************************************************************************** */

/*Creamos la clase de nuestro personaje pollo*/
class POLLO{
	int x,y;
	int corazon;
	int vidas;
	public:
	POLLO(int xx, int yy, int corazoon, int vidaas): x(xx), y(yy), corazon(corazoon), vidas(vidaas){} /*Constructor del Pollo*/
	
	int X(){return x;}      /*Función que nos da las coordenadas del Pollo*/
	int Y(){return y;}      /*Directamente no podemos acceder a ellas, por que son privadas*/
	int Z(){return vidas;}
	
	void pintar();  /*Dibujamos el pollo*/
	void borrar();  /*Borra el pollo desoues de que cambiamos de posicion en la pantalla*/
	void mover();   /*Mueve el pollo en la consola*/ 
	void pintar_corazones();
	void disminuir_corazones(){corazon --;}  /*Función que decrementa en uno el atributo corazon*/
	void aumentar_vida(){vidas ++;}
	void moverX(int mx){x=mx;}
	void moverY(int my){y=my;}
	void aumentar_corazones(){corazon+=3;if(corazon>=9){corazon = 9;}}
	void morir();	
};

void POLLO::pintar(){   /* :: Nos permite accecder a los métodos de la clase*/
     /*Situamos el cursor en diferentes coordenadas para pintar nuestro pollo y escribimos un caracter*/
	 /*en esa coordenada*/
	gotoxy(x,y);     printf("   %c%c", 92,92);   
	gotoxy(x,y+1); printf("   %c%c%c", 40,248,40);
	gotoxy(x,y+2); printf("%c%c%c%c%c%c", 92,92,95,47,47,41);
	gotoxy(x,y+3); printf(" %c%c%c%c%c", 92,95,47,95,41);
	gotoxy(x,y+4); printf("   %c", 193);
} 

void POLLO::borrar(){
	gotoxy(x,y);   printf("       ");   /*  Escribimos un espacio en blanco para borrar los movimientos pasados*/
    gotoxy(x,y+1); printf("       "); /* del pollo, tantos espacios en blanco en una linea como hay de*/
    gotoxy(x,y+2); printf("       "); /* caracteres en una línea de la función pintar*/
    gotoxy(x,y+3); printf("       ");
    gotoxy(x,y+4); printf("       ");
}

void POLLO::mover(){
	    /*Condición que detecta si una tecla se ha presionado*/
		if (kbhit()){
			char tecla = getch(); /*getch guarda la tecla que se preisona en la variable tecla*/
			gotoxy(x,y);  /*Nos situamos en las coordenadas anteriores del cursor*/
			borrar();  /*Limpiamos la pantalla de los movimientos pasados*/
			/*Comparamos una variable char con una varialbe int, en esta situación el compilador
			  mira a que número correspone en código ASCI*/
			if (tecla==IZQUIERDA && x>3) x--;   /*Al presionar IZQUIERDA, la coordenada x decrementa en 1*/
			if (tecla==DERECHA && x+6<76) x++;   /*Al presionar DERECHA, la coordenada x aumenta en 1*/
			if (tecla==ARRIBA && y>4) y--;   /*Al presionar ARRIBA, la coordenada y decrementa en 1*/ 
			if (tecla==ABAJO && y+3<31) y++;   /*Al presionar ABAJO, la coordenada y aumenta en 1*/
			pintar();  /*Pintamos el pollo :)*/
		}
}  

/*Barra de vida*/
void POLLO::pintar_corazones(){
	gotoxy(50,2);printf("Vidas %d", vidas);
	gotoxy(64,2); printf("Salud");
	gotoxy(70,2); printf("         ");
	for(int i = 0; i<corazon; i++){      /*llena la barra de salud*/
		gotoxy(70+i,2);printf("%c", 3); /*Escribimos caracter corazón*/
	}
}
 /*Funcion que mata al Pollo*/
void POLLO::morir(){
	if(corazon == 0 || corazon < 0){
		borrar();
		gotoxy(x,y);   printf("  **  ");   /*Simulamos una explosion del pollo*/
		gotoxy(x,y+1); printf(" **** ");
		gotoxy(x,y+2); printf("  **  ");
		Sleep(200);                           /*200ms entre un imagen y la siguiente para simular movimiento*/
		borrar();                             
		gotoxy(x,y);   printf("* ** *"); 
		gotoxy(x,y+1); printf(" **** ");
		gotoxy(x,y+2); printf("* ** *");
		Sleep(200);
		borrar();
		vidas--;        /*Se decrementan las vidas en 1 */
		corazon = 3;  /*Reset de los corazones al valor inicial*/
		pintar_corazones();    /*pintamos de nuevo los corazones y la nave*/
		pintar();
	}
}

/* ********************************************************************************************* */

/*Creamos la clase piedra que tendremos que esquivar durante le juego*/
class PIEDRA{
	int x,y,z;
	public:
	PIEDRA(int xx, int yy, int zz): x(xx), y(yy), z(zz){}
	int X(){return x;} int Y(){return y;}
	int velocidad(int vel){z=vel;}
	void pintar();
	void mover();
	/*Función para detectar colisión entre el pollo y la piedra*/
	void choque(class POLLO &p);  /*parametro de entrada de clase pollo, con &, ya que lo estaremos modificando*/
};

void PIEDRA::pintar(){
	gotoxy(x,y); printf("%c",184);
}

void PIEDRA::mover(){
	gotoxy(x,y);printf(" ");  /*El espacio en blanco borra la posición anterior*/
	x=x-z;  /*Simula la caída de la piedra*/
	/*Fijamos las piedras dentro del límite del cuadro del juego*/
	if(x <3){
    /*Coordenadas en x al azar dentro de los límites, coordenada 'y' fijada en 76 para que vuelva a caer*/
            /*La función rand se encuentra dentro de la biblioteca stdlib.h*/                   
		y = rand()%27 + 4;  /*nos da un valor al azar entre 4 y 31 para la coordenada x*/
		x=76; /*subimos la piedra de nuevo al orignen*/
	} 
	pintar(); /*Pintamos la piedra*/      
}

void PIEDRA::choque(class POLLO &p){
	/*Condición para detectar choque*/
	if(y>=p.Y() && y<=p.Y()+4 && x>=p.X() && x<= p.X()+5){   /*Se Han de cubrir los límites de*/
                                                             /*colisión con el tamaño del Pollo*/
        gotoxy(p.X(),p.Y());printf("   %c%c %c", 92,92,33);  /*Escribimos un '!' cada que nos pegan*/
		Sleep(100);
        p.borrar(); /*Limpiamos el pollo de cualquier piedra, ya que aveces no se borraba la piedra por sí sola*/                                                     
		p.disminuir_corazones();  /*Decrementamos en 1 los corazones*/
		p.pintar();               /*Volvemos a pintar el pollo, ya que al pasar una piedra por encima/* 
                                  /*se borra parte del pollo*/
		p.pintar_corazones();     /*Actualizamos los corazones*/
		y = rand()%27 + 4;        /*Regresamos la piedra a su posición inicial*/
		x=76;
	}
}

/* ************************************************************************************************* */
/*Creamos la clase escupitajo, es la saliba que lanza el pollo para destruir las piedras*/
class ESCUPITAJO{
	int x,y;
	public:
	ESCUPITAJO(int xx, int yy):x(xx),y(yy){}
	int X(){return x;} int Y(){return y;}
	void mover();      /*Función que mueve el esucpitajo horizontalmente saliendo desde le pico del pollo*/
	bool eliminar();   /*Elimina el escupitajo cuándo llega al límite de la consola*/
};

void ESCUPITAJO::mover(){
	gotoxy(x,y);printf(" ");
	x++;
	gotoxy(x,y);printf("%c",16);
}

bool ESCUPITAJO::eliminar(){
	if (x==76) return TRUE;
	return FALSE;
}

/* ************************************************************************************************* */

/*Creamos la clase zanahoria que nos da 3 corazones y una vida mas*/
class zanahoria{
	int x,y;
	bool ap;
	public:
	zanahoria(int xx, int yy, bool aparecio):x(xx),y(yy),ap(aparecio){}
	int X(){return x;} int Y(){return y;}
	bool a(){return ap;}
	void pintar(); 
	void borrar();
	void aparecer();
	void desaparecer(); 	
};

void zanahoria::pintar(){
	gotoxy(x,y);  printf("%c%c%c%c",95,92,47,95);
	gotoxy(x,y+1);printf("%c  %c",92,47);
	gotoxy(x,y+2);printf(" %c%c",92,47);	
}

void zanahoria::borrar(){
	gotoxy(x,y);  printf("    ");
	gotoxy(x,y+1);printf("    ");
	gotoxy(x,y+2);printf("    ");	
}

void zanahoria::aparecer(){
	x=rand()%68+4;
	y=rand()%25+5;
	gotoxy(x,y);
	int aux = rand()%100; 
	if(aux == 0){
	pintar(); 
	ap = TRUE;
	}
}
void zanahoria::desaparecer(){
	bool desaparece = FALSE;
	int aux = rand()%100; 
	if(aux == 0){desaparece = TRUE;}
	if(desaparece == TRUE){
	gotoxy(X(),Y());
	borrar();
	}
}


/* ************************************************************************************************* */

int main(){
	bool game_over = FALSE;  /*Variable que finaliza el juego*/
	bool paus = FALSE; 
	bool continuar =FALSE;
	bool dobleTiro= FALSE; bool tripleTiro= FALSE;
	int multPuntosPiedra = 1; int auxPiedra = 1; int multPuntosExeX = 1;
	int nivel = 1; int auxNivel = 2;
	int velPied = 1;
	
	ocultarCursor();  /*Ocultamos el cursor de la pantalla para que quede mas guai*/
	pintar_limites();
	POLLO n(7,20,3,3);   /*Construimos el objeto Pollo*/
	/*Pantalla de inicio */
	gotoxy(33,8);printf("!!JUEGA POLLO MANIA!!");
	gotoxy(25,11);printf("   Presiona ENTER para continuar");
	gotoxy(13,13);printf("        Salva al pollo con las flechas del teclado");
	gotoxy(8,15);printf(" Escupe saliba corrosiva y destruye las piedras presionando 'a'");
	gotoxy(6,17);printf(" Si quieres ir por un cafe, presiona pausa con la barra de espacio ");
	gotoxy(18,19);printf("Presiona ESC si... quieres terminar de jugar :(");
	n.moverX(35);n.moverY(22);n.pintar();   n.moverX(15);n.moverY(25);n.pintar();   n.moverX(55);n.moverY(25);n.pintar();
	/*Bcule pantalla de inicio*/
	while(!continuar){
		if(kbhit()){
			char tecla = getch();
			if (tecla == 13){continuar = TRUE;}
		}
        for (int a = 21;a<31; a++){
			for(int i = 3; i<76 ; i++){
			gotoxy(i, a);printf(" ");     
			}
		}
        n.moverX(15);n.moverY(22);n.pintar(); n.moverX(36);n.moverY(25);n.pintar(); n.moverX(55);n.moverY(22);n.pintar();
        Sleep(500);
        for (int a = 21;a<31; a++){
			for(int i = 3; i<76 ; i++){
			gotoxy(i, a);printf(" ");     
			}
		}  
        n.moverX(15);n.moverY(25);n.pintar(); n.moverX(36);n.moverY(22);n.pintar(); n.moverX(55);n.moverY(25);n.pintar();
        Sleep(500);
	}
	
	continuar = FALSE;
	
	/*Bucle que borra la pantalla*/
	for (int a = 4;a<32; a++){
		for(int i = 3; i<76 ; i++){
		gotoxy(i, a);printf(" ");     
		}
	}
	gotoxy(37,15);printf("3!");
	Sleep(1000);
	gotoxy(37,15);printf(" ");
	gotoxy(37,15);printf("2!!");
	Sleep(1000);
	gotoxy(37,15);printf(" ");
	gotoxy(37,15);printf("1!!");
	Sleep(1000);
	gotoxy(37,15);printf(" ");
	gotoxy(27,15);printf("YA!!!! SALVA TU POLLO!!!!");
	Sleep(1000);
	
	/*Bucle que borra la pantalla*/
	for (int a = 4;a<32; a++){
		for(int i = 3; i<76 ; i++){
		gotoxy(i, a);printf(" ");     /*Línea superior*/
		}
	}
	
	n.moverX(7);n.moverY(13);n.pintar();n.pintar();
	n.pintar_corazones();
	zanahoria z(rand()%68+4,rand()%25+5, FALSE);
	
	int a = 1; int aux = 0; int aux2 = 500;   /*variables auxiliares para subir vidas cada 500,550,600... puntos*/
	
	int puntos = 0;  /*Puntuación del juego*/ 
	 
	/*Creamos una lista de la clase escupitajo, cada objeto se creara cuando se detecte una tecla presionada*/
	list<ESCUPITAJO*> E;    /*El puntero '*' indíca reservar memoria para los escupitajos manualmente*/
	list<ESCUPITAJO*>::iterator it;
	/*Lista donde estan las piedras a esquivar en el juego*/
	list<PIEDRA*> P;
	list<PIEDRA*>::iterator itP;
	for (int i = 0; i<7; i++){  /*Creamos 7 piedras*/   
		P.push_back(new PIEDRA(rand()%70 + 6,rand()%27 + 4, velPied));    /*Coordenadas al azar*/
	} 
	/*Ejecuta constantemente la función gotoxy mientras game_over sea falso*/
	while(!game_over){
		gotoxy(4,2);printf("Puntuacion: %d", puntos);/*Imprimimos la puntuación*/
		gotoxy(1,1);printf("auxpiedra %d", auxPiedra);  gotoxy(15,1);printf("multPiedra %d", multPuntosPiedra); gotoxy(30,1);printf("multEjeX %d", multPuntosExeX); gotoxy(45,1);printf("Nivel %d", nivel);
		if (paus == FALSE){
		

		/*Condicional para crear un escupitajo cuándo presionamos la tecla a*/
		if(kbhit() && n.X()<70){
			char tecla = getch();
			if (tecla == 'a'){
				E.push_back(new ESCUPITAJO(n.X()+6,n.Y()+1));  /*Creamos un nuevo objeto escupitajo con*/
				                                          /*push_back en las mismas coordenadas que el pollo*/
				/*Creamos un segundo escupitajo a partir del tercer nivel*/
				if(dobleTiro == TRUE){E.push_back(new ESCUPITAJO(n.X()+6,n.Y()+2));}
				/*Creamos un tercer escupitajo a partir del quinto nivel*/
				if(tripleTiro == TRUE){E.push_back(new ESCUPITAJO(n.X()+6,n.Y()+3));}                                          
			}
			if (tecla==32){paus = TRUE;} 
			if (tecla==27){game_over = TRUE;}  
		}
		
		/*Bucle con el que hacemos que los escupitajos se muevan, para todos los objetos de la lista */
		for(it = E.begin(); it != E.end(); it++){/* El iterador obtiene el valor desde el primer elemento  */ 
                                                 /* de la lista hasta el último */
            (*it)->mover();  /*Con el '*' podemos acceder a modificar el objeto de la posición en la que estamos*/
		    if((*it)->eliminar()){   /*Eliminamos el objeto de la lista una vez ha llegado al límite de la consola*/
    			gotoxy((*it)->X(),(*it)->Y());   /*Nos situamos en las coordenadas del escupitajo*/
    			printf(" ");    /*Borramos de la pantalla en caso de que siga ahí*/
    			delete(*it);    /*Eliminamos el elemento de la lista*/
    			it = E.erase(it);  /*Reconectamos la lista para que no nos de error*/
    		} 
		}
		
		/*Bucle para recorrer la lista de piedras*/
		for(itP = P.begin(); itP != P.end(); itP++){
			(*itP)->velocidad(velPied);
			(*itP)->mover();
			(*itP)->choque(n);
		}
		
		/*Bucle para subir en 1 la puntuación cuáno una piedra llega al otro lado y que sume en 1 el contador de los 500 puntos para una vida mas*/
		for(itP = P.begin(); itP != P.end(); itP++){
			if((*itP)->X() <= 4 ){puntos+= 1*multPuntosExeX; aux+= 1*multPuntosExeX; auxPiedra+=1*multPuntosExeX;}
		}
		
		/*Bucle para detectar colisión entre escupitajo y piedras*/
		for(itP=P.begin();itP!=P.end();itP++){  /*Recorremos la lista de las piedras*/
			for(it=E.begin();it!=E.end();it++){   /*Recorremos la lista de los escupitajos*/
			    /*Compraramos la coordenada de escupitajo con piedra, si tienen la misma coordeanada, o estan a una coordenada de colisionar, o a dos coordenadas en modo dificultad medio */
				if((*itP)->Y()==(*it)->Y() &&((*itP)->X() ==(*it)->X() || (*itP)->X()-1 ==(*it)->X() || (*itP)->X()-2 ==(*it)->X())){
					gotoxy((*it)->X(),(*it)->Y());printf(" ");/*Sí hay colisión borramos el escupitajo*/
					delete(*it); /*Eliminamos el escupitajo de la lista*/
					it = E.erase(it); /*Resonectamos el hilo de la lista*/ 
				    P.push_back(new PIEDRA(76,rand()%27 + 4, velPied));/*Antes de destuir la piedra creamos una nueva, ya que si solamente destruimos nos quedamos sin piedras despues*/
					/*Dibujamos la corrosión de las piedras a causa del escupitajo*/
					gotoxy((*itP)->X(),(*itP)->Y());printf(" ");
					gotoxy((*itP)->X(),(*itP)->Y());printf("%c",42);
					Sleep(50);
					gotoxy((*itP)->X(),(*itP)->Y());printf(" ");
					delete(*itP);
					itP = P.erase(itP);
					puntos+= 5*multPuntosPiedra;/*Actualizamos la puntuación*/
					aux+=5*multPuntosPiedra;
					auxPiedra+=5*multPuntosPiedra;
				}
			} 
		}
		
		
		
		/*Bucle que nos da una vida cada 500 puntos, y aumenta en 50 para la próxima vez*/
		if(aux >= aux2){
			n.aumentar_vida();
			n.aumentar_corazones();
			n.pintar_corazones();
			aux = 0;
			aux2 = 500+(50*a);
			a+=1;
		}
		
		if(auxPiedra >= 800){multPuntosPiedra = 2;}
		if(auxPiedra >= 2000){multPuntosPiedra = 3;}
		if(auxPiedra >= 1000){multPuntosExeX= 2;}
		if(auxPiedra >= 2300){multPuntosExeX= 3;}
		
		/*Bucle para detectar colisión entre zanahorias y piedras*/
		for(itP=P.begin();itP!=P.end();itP++){  /*Recorremos la lista de las piedras*/
			    /*Compraramos la coordenada de zanahoria con piedra, si tienen la misma coordeanada, o estan a una coordenada de colisionar, o a dos coordenadas en modo dificultad medio */
				if((*itP)->Y()==z.Y() &&((*itP)->X() ==z.X() || (*itP)->X()-4 ==z.X() || (*itP)->X()-5 ==z.X()) ||
					(*itP)->Y()==z.Y()+1 &&((*itP)->X() ==z.X() || (*itP)->X()-4 ==z.X() || (*itP)->X()-5 ==z.X()) ||
						(*itP)->Y()==z.Y()+2 &&((*itP)->X() ==z.X() || (*itP)->X()-4 ==z.X() || (*itP)->X()-5 ==z.X())){
					P.push_back(new PIEDRA(76,rand()%27 + 4,velPied));
					gotoxy((*itP)->X(),(*itP)->Y());printf(" ");/*Sí hay colisión borramos la piedra*/
					delete(*itP); /*Eliminamos el escupitajo de la lista*/
					itP = P.erase(itP); /*Resonectamos el hilo de la lista*/ 
				} 
		}
		/*Bucle para detectar colisión entre zanahorias y escupitajos*/
		for(it=E.begin();it!=E.end();it++){
			if((*it)->Y()==z.Y() &&((*it)->X() ==z.X() || (*it)->X()+1 ==z.X() || (*it)->X()+2 ==z.X()) ||
				(*it)->Y()==z.Y()+1 &&((*it)->X() ==z.X() || (*it)->X()+1 ==z.X() || (*it)->X()+2 ==z.X()) ||
						(*it)->Y()==z.Y()+2 &&((*it)->X() ==z.X() || (*it)->X()+1 ==z.X() || (*it)->X()+2 ==z.X())){
				gotoxy((*it)->X(),(*it)->Y());printf(" ");/*Sí hay colisión borramos el escupitajo*/
					delete(*it); /*Eliminamos el escupitajo de la lista*/
					it = E.erase(it); /*Resonectamos el hilo de la lista*/
			}
		}
		
		if(puntos>=450 && velPied == 1){velPied = 2;}
			
		if (puntos>=(800*nivel) && nivel == 1){nivel = nivel +1;}
		if (puntos>=(800*nivel) && nivel == 2){nivel = nivel +1;}
		if (puntos>=(800*nivel) && nivel == 3){nivel = nivel +1;}
		if (puntos>=(800*nivel) && nivel == 4){nivel = nivel +1;}
		if (puntos>=(800*nivel) && nivel == 5){nivel = nivel +1;}
			
		n.morir();
	    n.mover();             
		}/*end while !PASUE*/
		
		if (nivel == auxNivel){
			continuar = FALSE;
			for (int a = 4;a<32; a++){
				for(int i = 3; i<76 ; i++){
				gotoxy(i, a);printf(" ");     /*Línea superior*/
				}
			}
			auxNivel = auxNivel+1;
			n.aumentar_vida();n.aumentar_vida();
			n.aumentar_corazones();n.aumentar_corazones();
			n.pintar_corazones();
			
			if (nivel == 3){ dobleTiro = TRUE;}
			if (nivel == 5){ tripleTiro = TRUE;}
			
			P.push_back(new PIEDRA(rand()%70 + 6,rand()%27 + 4, velPied));
			P.push_back(new PIEDRA(rand()%70 + 6,rand()%27 + 4, velPied));
			gotoxy(25,10);printf("HAS ALCANZADO %d PUNTOS O MAS", puntos);
			gotoxy(25,12);printf("NIVEL %d YAJU!!!! SIGUE ASI!! =D", nivel);
			gotoxy(25,18);printf("       Presiona ENTER");	
			while(!continuar){
				if(kbhit()){
				char tecla = getch();
				if (tecla == 13){continuar = TRUE;}
				}
				Sleep(30);
			}/*end while*/
			for (int a = 4;a<32; a++){
				for(int i = 3; i<76 ; i++){
				gotoxy(i, a);printf(" ");     
				}
			}
			n.pintar();
		}/*end if*/
		
		if(kbhit()){
			char tecla = getch();
			if (tecla==32){paus = FALSE;}                                      
			}
		
        if(n.Z()<0){game_over=TRUE;}
		
		Sleep(30);			
	}/*END !GAME_OVER*/
	
	/*Bucle que borra la pantalla cuándo es GAME OVER*/
	for (int a = 4;a<32; a++){
		for(int i = 3; i<76 ; i++){
		gotoxy(i, a);printf(" ");     /*Línea superior*/
		}
	}
	/*Mensaje que sale cuándo es game over*/
	gotoxy(27,10);printf("Te han echo pollo rostizado!!"); 
	gotoxy(27,15);printf("%c FIN DEL JUEGO MI AMIGO %c",2, 2);
	Sleep(6000);
	gotoxy(37,32);
	return 0;
}/*END MAIN*/