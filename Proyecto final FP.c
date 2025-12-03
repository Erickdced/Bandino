#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// Prueba
void admin(int);
void cliente(int);
void menu();
void guardarTicket(const char *);
void obtenerFechaHora(char *, int);
float montoA();
float montoB();
float Transferir(float montoTransferencia);
float Invertir(float montoInvertir);
void ticketRetiro(float, float);
void ticketTransferencia(char[], float, float);
void ticketIngreso(float, float, float);
void ticketInversion(float, float, float);
void ticketConsulta(float);

int x, y, leido; //"x" y "y" son variables que sirven en caso de que el usuario
                 //tenga que crear un nuevo usuario y contrasenia
int opc;
float montoActual = 500, montoRetirado, montoIngresado, montoFinal, montoTransferencia, montoInvertir;

void trim_newline(char *s) {
  size_t len = strlen(s);
  if (len > 0 && s[len - 1] == '\n')
    s[len - 1] = '\0';
}
void clear_stdin(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
  FILE *archivoUsuario, *archivoContrasenia; // Los archivos en espaniol corresponden al menu de administrador
  FILE *archivoUser, *archivoPass; // Estos archivos corresponden a la parte de clientes
  FILE *clientes;
  char uG[50], cG[50], qG[50], pG[50];
  char u[50], c[50], q[50], p[50];
  int intentos, accesoConcedido;
  do {
    intentos = 0;
    accesoConcedido = 0;

    menu();

    switch (opc) {
    case 1:
      do {
        printf("1- Crear nueva cuenta\n");
        printf("2- Inciar sesion\n");
        printf("3- Salir\n");
        printf("Digite su opcion\n");
        do {
          leido = scanf("%i", &x);
          if (leido == 0) {
            printf("Debe ingresar un entero\n");
            while (getchar() != '\n');
          }
        } while (leido == 0);
        if (x == 1) {
          archivoUsuario = fopen("usuario.txt", "a+");
          archivoContrasenia = fopen("contrasenia.txt", "a+");
          printf("Ingrese su nuevo usuario administrador\n");
          clear_stdin();
          fgets(uG, 50, stdin);
          trim_newline(uG);
          printf("Ingrese su nueva contrasenia de administrador\n");
          scanf("%49s", &cG);
          fprintf(archivoUsuario, "%s\n", uG);
          fprintf(archivoContrasenia, "%s\n", cG);
          fclose(archivoUsuario);
          fclose(archivoContrasenia);
        } else if (x == 2) {
          while (intentos < 3) {
            archivoUsuario = fopen("usuario.txt", "r");
            archivoContrasenia = fopen("contrasenia.txt", "r");
            fscanf(archivoUsuario, "%s\n", uG);
            fscanf(archivoContrasenia, "%s\n", cG);
            fclose(archivoUsuario);
            fclose(archivoContrasenia);
            printf("Ingrese su usuario administrador\n");
            clear_stdin();
            fgets(u, 50, stdin);
            trim_newline(u);
            printf("Ingrese su contrasenia de administrador\n");
            scanf("%49s", &c);

            if (strcmp(u, uG) == 0 && strcmp(c, cG) == 0) { // Comparamos las cadenas de caracteres para verificar si son iguales
              accesoConcedido = 1;
              intentos = 3;
            } else {
              printf("Usuario o contrasenia incorrectos\n");
              intentos++;
            }
          }
        } else if (x == 3) {
          printf("Volviendo al menu\n");
        } else {
          printf("Opcion invalida\n");
        }
      } while (x != 3);
      if (accesoConcedido == 1) {
        admin(opc);
      }
      if (accesoConcedido == 0) {
        printf("Acceso denegado\n");
        accesoConcedido = 2;
      } else {
        printf("Opción no válida\n");
      }
      break;
    case 2:
      archivoUser = fopen("user.txt", "a+");
      archivoPass = fopen("pass.txt", "a+");
      if (y == 0) {
        printf("Ingrese su nuevo usuario de cliente\n");
        clear_stdin();
        fgets(qG, 50, stdin);
        trim_newline(qG);
        printf("Ingrese su nueva contrasenia de cliente\n");
        scanf("%49s", &pG);
        fprintf(archivoUser, "%s\n", qG);
        fprintf(archivoPass, "%s\n", pG);
        fclose(archivoUser);
        fclose(archivoPass);
        do {
          printf("Ingrese 500 pesos para crear su cuenta\n");
          scanf("%f", &montoActual);
          if (montoActual != 500) {
            printf("Opcion de dinero invalida\n");
          }
        } while (montoActual != 500);
        y++;
      }
      printf("Ingrese el usuario y contraseña de cliente\n");
      scanf("%s %s", &q, &p);
      if (strcmp(q, qG) == 0 && strcmp(p, pG) == 0) {
        accesoConcedido = 1;
      } else {
        printf("Usuario o contrasenia incorrectos\n");
      }
      if (accesoConcedido == 1) {
        cliente(opc);
      }
      break;
    case 3:
      printf("BANDINO\n");
      printf("Programadores:\n");
      printf("Alarcon Fuertes Diego Ricardo Wenceslao\t wenceslaoaf@gmail.com\n");
      printf("Emiliano Olivares Villeda\t emi.olivill@gmail.com\n");
      printf("Saul Castaneda Molina\t saulcastenedam.11@gmail.com\n");
      printf("Katherin Paola Torres Maldonado maldonadokatherinmal@gmail.com	\n");
      break;

    case 4:
      printf("Saliendo del programa\n");
      break;

    default:
      printf("Opcion no valida\n");
      break;
    }
  } while (opc != 4);
  return 0;
}

void menu() {
  printf("***BIENVENIDO A BANDINO***\n");
  printf("Menu de opciones\n");
  printf("1- Administrador\n");
  printf("2- Cliente\n");
  printf("3- Contactar programadores\n");
  printf("4- Salir\n");
  printf("Digite su opcion\n");
  do {
    leido = scanf("%i", &opc);
    if (leido == 0) {
      printf("Debe ingresar un entero\n");
      while (getchar() != '\n'); // Con esto evitamos que el menu entre en un bucle en caso de que el usuario
    }                            //ingrese una variable de tipo caracter
  } while (leido == 0);
}

void admin(int opc1) {
  printf("\n");
  printf("Acceso concedido\n");
  printf("Menu de Administrador\n");
  printf("1- Aniadir clientes\n");
  printf("2- Modificar datos del cliente\n");
  printf("3- Modificar dinero del cliente\n");
  printf("4- Visualizar las transacciones del cliente\n");
  printf("5- Eliminar algun cliente\n");
  printf("Digite su opcion\n");
  do {
    leido = scanf("%i", &opc1);
    if (leido == 0) {
      printf("Debe ingresar un entero\n");
      while (getchar() != '\n')
        ;
    }
  } while (leido == 0);
}
void cliente(int opc2) {
  printf("\n");
  printf("Acceso concedido\n");
  printf("Menu de Cliente\n");
  printf("1- Retirar dinero\n");
  printf("2- Hacer transferencias\n");
  printf("3- Ingresar dinero a su cuenta\n");
  printf("4- Consultar sus datos\n");
  printf("5- Invertir en la bolsa\n");
  printf("Digite su opcion\n");
  do {
    leido = scanf("%i", &opc2);
    if (leido == 0) {
      printf("Debe ingresar un entero\n");
      while (getchar() != '\n');
    }
  } while (leido == 0);
  switch (opc2) {
  case 1:
    printf("Tu saldo actual es: %.4f\n", montoActual);
    do {
      printf("Ingrese la cantidad de dinero que desea retirar\n");
      scanf("%f", &montoRetirado);
      if (montoRetirado > montoActual || montoRetirado < 0) {
        printf("Cantidad de dinero ingresada invalida, ingrese una nueva cifra\n");
      }
    } while (montoRetirado > montoActual || montoRetirado < 0);
    montoActual = montoA();
    printf("Su saldo final es: %.2f\n", montoActual);
    printf("Dinero Retirado: %.2f\n", montoRetirado);
    ticketRetiro(montoRetirado, montoActual);
    break;
  case 2:
    printf ("Ingrese la clabe interbancaria (18 digitos) de la cuenta a la que desea transferir el dinero\n");
    char cuenta[18];
    scanf ("%18s", &cuenta);
    printf ("Escriba el nombre del destinatario\n");
    char nombre [50];
    scanf ("%s", &nombre);
    printf ("Ingrese la cantidad de dinero que desea transferir \n");
    scanf ("%f", &montoTransferencia);
    montoActual = Transferir (montoTransferencia);
    ticketTransferencia(nombre, montoTransferencia, montoActual);
    break;
  case 3:
    do {
      printf("Ingrese la cantidad de dinero que desea ingresar a su cuenta\n");
      scanf("%f", &montoIngresado);
      if (montoIngresado < 0) {
        printf("Cantidad de dinero ingresada invalida, ingrese una nueva cifra\n");
      }
    } while (montoIngresado < 0);
    montoFinal = montoB();
    printf("Saldo ingresado: %.2f\n", montoIngresado);
    printf("Saldo final: %.2f\n", montoFinal);
    printf("Saldo inicial: %.2f\n", montoActual);
    montoActual = montoB();
    ticketIngreso(montoIngresado, montoActual, montoFinal);
    break;
  case 4:
    printf("Saldo actual: %.2f\n", montoActual);
    ticketConsulta(montoActual);
    break;
  case 5:
    printf ("Ingrese la cantidad de dinero que desea invertir \n");
    scanf ("%f", &montoInvertir);
    montoActual = Invertir (montoInvertir);
    break;
  default:
    printf("Opcion no valida\n");
  }
}
float montoA(){
    return montoActual - montoRetirado;
}
float montoB(){
    return montoActual + montoIngresado;
}
float Transferir (float montoTransferencia){
    if (montoTransferencia <= 0){
        printf ("Cantidad de dinero invalida, necesita ingresar una cantidad mayor a 0 \n");
        return montoActual;
    }
    else if (montoTransferencia > montoActual){
        printf ("Cantidad de dinero no disponible, ingrese una cantidad menor a su saldo actual \n");
        return montoActual;
    }
    montoActual -= montoTransferencia;
        printf ("Transferencia exitosa, su saldo actual es %2.f\n", montoActual);
        printf("Cantidad transferida: %.2f\n", montoTransferencia);
        printf("Saldo actual: %.2f\n", montoActual);
        return montoActual;
}
float Invertir (float montoInvertir){
    if (montoInvertir <= 0){
        printf ("Cantidad de dinero invalida, ingrese la cantidad de dinero valida \n");
        return montoActual;
    }
    else if (montoInvertir > montoActual){
        printf ("Cantidad de dinero no disponible, ingrese una cantidad de dinero menor \n");
        return montoActual;
    }
    //Creamos la semilla para generar numeros aleatorios
    srand(time(NULL));
    float porcentaje = (rand() % 16 - 5);  //Generamos un numero aleatorio entre -5 y 10
    float ganancia = montoInvertir * (porcentaje / 100); //Calculamos la ganancia, pero convertida a porcentaje
    montoActual= montoActual + ganancia;
    printf ("RESULTADOS DE LA INVERSION \n");
    if (ganancia > 0) {
            printf("¡Ganancia! Obtuviste un %.2f%%\n", porcentaje);
            printf("Ganaste: %.2f\n", ganancia);
        } else if (ganancia < 0) {
            printf("Perdiste un %.2f%%\n", porcentaje);
            printf("Perdiste: %.2f\n", -ganancia);
        } else {
            printf("La inversión quedó igual (0%%).\n");
        }
        printf("Tu nuevo saldo es: %.2f\n", montoActual);
        char fechaHora[20];
        obtenerFechaHora(fechaHora, sizeof(fechaHora));
        char ticket[200];
        sprintf(ticket, "Ticket de Inversión\nFecha y Hora: %s\nMonto Invertido: %.2f\nGanancia: %.2f\nSaldo Actual: %.2f\n\n", fechaHora,           montoInvertir, ganancia, montoActual);
        guardarTicket(ticket);
        printf("Ticket de inversión generado y guardado.\n");
        printf("%s", ticket);
        return montoActual;
    }
    void guardarTicket(const char *texto) {
        FILE *ticket = fopen("tickets.txt", "a");
            if (!ticket) {
            printf("Error al abrir el archivo de tickets.\n");
            return;
        }
        fputs(texto, ticket);
        fclose(ticket);
    }
    void obtenerFechaHora(char *fechaHora, int tamano){
        time_t tiempoActual = time(NULL);
        struct tm *tiempoLocal = localtime(&tiempoActual);
        strftime(fechaHora, tamano, "%Y-%m-%d %H:%M:%S", tiempoLocal);
    }
    void ticketRetiro(float montoRetirado, float montoActual){
        char fechaHora[20];
        obtenerFechaHora(fechaHora, sizeof(fechaHora));
        char ticket[200];
        sprintf(ticket, "Ticket de Retiro\nFecha y Hora: %s\nMonto Retirado: %.2f\nSaldo Actual: %.2f\n\n", fechaHora, montoRetirado,                montoActual);
        guardarTicket(ticket);
        printf("Ticket de retiro generado y guardado.\n");
        printf("%s", ticket);
    }
    void ticketTransferencia(char nombre[], float montoTransferencia, float montoActual){
        char fechaHora[20];
        obtenerFechaHora(fechaHora, sizeof(fechaHora));
        char ticket[200];
        sprintf(ticket, "Ticket de Transferencia\nFecha y Hora: %s\nNombre del Destinatario: %s\nMonto Transferido: %.2f\nSaldo Actual:               %.2f\n\n", fechaHora, nombre, montoTransferencia, montoActual);
        guardarTicket(ticket);
        printf("Ticket de transferencia generado y guardado.\n");
        printf("%s", ticket);
    }
    void ticketIngreso(float montoIngresado, float montoActual, float montoFinal){
        char fechaHora[20];
        obtenerFechaHora(fechaHora, sizeof(fechaHora));
        char ticket[200];
        sprintf(ticket, "Ticket de Ingreso\nFecha y Hora: %s\nMonto Ingresado: %.2f\nSaldo Actual: %.2f\nSaldo Final: %.2f\n\n", fechaHora,         montoIngresado, montoActual, montoFinal);
        guardarTicket(ticket);
        printf("Ticket de ingreso generado y guardado.\n");
        printf("%s", ticket);
    }
    void ticketConsulta(float montoActual){
        char fechaHora[20];
        obtenerFechaHora(fechaHora, sizeof(fechaHora));
        char ticket[200];
        sprintf(ticket, "Ticket de Consulta\nFecha y Hora: %s\nSaldo Actual: %.2f\n\n", fechaHora, montoActual);
        guardarTicket(ticket);
        printf("Ticket de consulta generado y guardado.\n");
        printf("%s", ticket);
    }
