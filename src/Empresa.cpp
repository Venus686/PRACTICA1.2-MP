#include "Empresa.h"


//el constructor de la clase empresa debe crear un array dinámico de tamaño inicial 10
//debe inicializar a 0 los contadores de clientes (ncli) y contratos (ncon)
//y debe inicializar la constante nmaxcli a 100 y la variable nmaxcon a 10
Empresa::Empresa():nmaxcli(100) {
     this->ncli=0;
     this->ncon=0;
     this->contratos=new Contrato *[10]; //inicialmente capacidad para 10 Contratos
     this->nmaxcon=10;
}
//el destructor debe, además de eliminar el array dinámico creado en el constructor,
//eliminar los objetos clientes y contratos apuntados por ambos arrays
Empresa::~Empresa() {
     for(int i=0; i<this->ncon; i++) { //primero elimino los objetos contratos
        delete this->contratos[i];
     }
     delete [] this->contratos; //luego elimino el array de punteros
     for(int i=0; i<this->ncli; i++) { //primero elimino los objetos clientes
        delete this->clientes[i];
     }
    //delete [] this->clientes; //ERROR el array clientes no es dinámico
}

//método auxiliar usado por el método crearContrato
int Empresa::altaCliente(Cliente *c) { //añade cliente apuntado por c al array clientes
     int pos=-1; //devuelve -1 si no cabe y la posición donde
     if (this->ncli<nmaxcli) { //donde lo he metido si cabe
         this->clientes[this->ncli]=c;
         pos=this->ncli;
         this->ncli++;
     }else {
         cout << "Lo siento, el cupo de clientes esta lleno";
         pos=-1;
     }
     return pos;
}
//método auxiliar usado por el método crearContrato
int Empresa::buscarCliente(long int dni) const { //si no existe devuelve -1 y si existe
    int pos=-1;
     for (int i=0; i<this->ncli;i++){
        if(this->clientes[i]->getDni()==dni){
            pos=i;
            break;
        }
     }return pos;
}

int Empresa::nContratosTP() const {
    int count = 0; // Contador para los contratos de Tarifa Plana

    // Recorrer todos los contratos y contar los que son de tipo ContratoTP
    for (int i = 0; i < ncon; ++i) {
        // Usar dynamic_cast para verificar si el contrato es de tipo ContratoTP
        if (dynamic_cast<ContratoTP*>(contratos[i]) != nullptr) {
            count++; // Incrementar el contador si es de tipo ContratoTP
        }
    }

    return count; // Retornar el número de contratos de Tarifa Plana
}

 int Empresa:: descuento(float porcentaje) const {

    int cont  = 0; // Contador para contratos Movil
    for (int i = 0; i < ncon; ++i) {
    ContratoMovil* movilContrato = dynamic_cast<ContratoMovil*>(contratos[i]);
        if (movilContrato) {
            movilContrato->setPrecioMinuto(movilContrato->getPrecioMinuto()*(100-porcentaje)/100);
            cont++;
        }
    }
        return cont;
}

void Empresa::crearContrato() { //EL ALUMNO DEBE TERMINAR DE IMPLEMENTAR ESTE METODO
 long int dni;
 int pos;
 cout << "Introduzca dni: ";
 cin >> dni;
 //supongo que hay un metodo buscarCliente(dni) que devuelve -1 si no existe y si
 //existe devuelve la posicion del cliente en el array this->cli
 pos=this->buscarCliente(dni);
 if (pos==-1) { //el cliente no existe y hay que darlo de alta
     int dia, mes, anio;
     char nombre[100];
     Cliente *c; //NO CREO NINGUN CLIENTE SINO SOLO UN PUNTERO A CLIENTE
     cout << "Nombre del cliente: ";
     cin.ignore();
     cin.getline (nombre,100);
     cout << "Introduce Fecha (dd mm aaaa): ";
     cin >> dia >> mes >> anio;
     c=new Cliente(dni, nombre, Fecha(dia, mes, anio));
     pos=this->altaCliente(c); //OJO HAY QUE IMPLEMENTARLO
 }
 //viendo cuanto vale la variable pos sé si el cliente se ha dado de alta o no
if (pos !=-1){
        int tipoContrato;
        int dia, mes, anio;
        int minutos;
        cout<<  "Tipo de Contrato a abrir: (1- Tafifa Plana, 2- Movil): ";
        cin>> tipoContrato;
         Contrato *nuevoContrato = nullptr;
    if (tipoContrato == 1) {
        cout<< "Fecha del contrato:"<<endl;
        cout<<"dia: ";
        cin>>dia;
        cout<<"mes: ";
        cin>>mes;
        cout<< "anio: ";
        cin>>anio;

        cout << "minutos hablados: ";
        cin >> minutos;

        // Crear y añadir el contrato de tarifa plana
            nuevoContrato = new ContratoTP(dni, Fecha(dia, mes, anio), minutos);

        } else if (tipoContrato == 2) { // Contrato Movil
            float precio;
            char nacionalidad[100]; // Para la nacionalidad
            cout<< "Fecha del contrato"<<endl;
            cout<<"dia: ";
            cin>>dia;
            cout<<"mes: ";
            cin>>mes;
            cout<< "anio: ";
            cin>> anio;
            cout << "minutos hablados: " ;
            cin >> minutos;
            cout << "Precio minuto: ";
            cin >> precio;
            cout << "Nacionalidad: ";
            cin >> nacionalidad;

            // Crear el contrato de tipo Movil
            nuevoContrato = new ContratoMovil(dni, Fecha(dia, mes, anio),precio,  minutos, nacionalidad);
        } else {
            cout << "Tipo de contrato no válido."<<endl;
            return;
        }

        // Añadir el contrato al array de contratos
        // Verificar si se necesita ampliar el array
        if (ncon >= nmaxcon) {
            // Duplicar el tamaño del array
            nmaxcon *= 2;
            Contrato **nuevoArray = new Contrato*[nmaxcon];
            for (int i = 0; i < ncon; ++i) {
                nuevoArray[i] = contratos[i]; // Copiar contratos existentes
            }
            delete[] contratos; // Liberar el antiguo array
            contratos = nuevoArray; // Asignar el nuevo array
        }

        // Lógica para insertar el nuevo contrato
        contratos[ncon++] = nuevoContrato; // Añadir el nuevo contrato y aumentar el contador
}
}

//el cliente existe o se ha dado de alta
 //PREGUNTAR QUE TIPO DE CONTRATO QUIERE Y LOS DATOS NECESARIOS
 //CREAR EL OBJETO CONTRATO CORRESPONDIENTE Y AÑADIR AL ARRAY
 //contratos UN PUNTERO A DICHO OBJETO


bool Empresa::cancelarContrato(int idContrato) {
    // Buscar el contrato con el idContrato proporcionado
    int pos = -1; // Inicializamos pos en -1 para indicar que no se ha encontrado el contrato
    for (int i = 0; i < ncon; ++i) {
        if (contratos[i]->getIdContrato() == idContrato) { // Supongamos que Contrato tiene un método getId()
            pos = i; // Guardamos la posición del contrato encontrado
            break; // Salimos del bucle una vez que hemos encontrado el contrato
        }
    }

    if (pos == -1) {
        cout << "Contrato no encontrado.\n";
        return false; // Si no se encontró el contrato, retornamos false
    }

    // Si hemos encontrado el contrato, proceder a eliminarlo
    delete contratos[pos]; // Liberamos la memoria del contrato

    // Compactar el array de contratos
    for (int i = pos; i < ncon - 1; ++i) {
        contratos[i] = contratos[i + 1]; // Desplazamos los contratos hacia la izquierda
    }
    ncon--; // Reducimos el contador de contratos

    cout << "Contrato cancelado exitosamente.\n";
    return true; // Retornamos true para indicar que se canceló exitosamente
}


bool Empresa:: bajaCliente(long int dni){
    int pos = buscarCliente(dni);
    if (pos == -1) {
        cout << "No se ha encontrado el cliente. "<<endl;
        return false;
    }

    ///Elimino el contrato de la persona
    int i=0;
    while (i<ncon){
        if (contratos[i]->getDniContrato()==dni){
            /*if (dynamic_cast<ContratoTP*>(contratos[i])) {
                cout << "Eliminando Tarifa Plana."<<endl;
            } else if (dynamic_cast<ContratoMovil*>(contratos[i])) {
                cout << "Eliminando Contrato Movil"<<endl;
            }*/
            delete contratos[i];
            for (int j=i; j<ncon-1;j++){
                contratos[j]=contratos[j+1]; // desplazo a la izquierda
            }
            ncon--;
        }else{
            i++;
        }
    }
    ///Elimino el cliente
    delete clientes[pos];
    for (int i = pos; i < ncli - 1; ++i) {
        clientes[i] = clientes[i + 1];
    }
    ncli--;
    return true;

}

void Empresa::cargarDatos() {
     Fecha f1(29,2,2001), f2(31,1,2002), f3(1,2,2002);
     this->clientes[0] = new Cliente(75547001, "Peter Lee", f1);
     this->clientes[1] = new Cliente(45999000, "Juan Perez", Fecha(29,2,2000));
     this->clientes[2] = new Cliente(37000017, "Luis Bono", f2);
     this->ncli=3;
     this->contratos[0] = new ContratoMovil(75547001, f1, 0.12, 110, "DANES"); //habla 110m a 0.12€/m
     this->contratos[1] = new ContratoMovil(75547001, f2, 0.09, 170, "DANES"); //habla 170m a 0.09€/m
     this->contratos[2] = new ContratoTP(37000017, f3, 250); //habla 250m (300m a 10€, exceso 0.15€/m)
     this->contratos[3] = new ContratoTP(75547001, f1, 312); //habla 312m (300m a 10€, exceso 0.15€/m)
     this->contratos[4] = new ContratoMovil(45999000, f2, 0.10, 202, "ESPAÑOL"); //habla 202m a 0.10/m
     this->contratos[5] = new ContratoMovil(75547001, f2, 0.15, 80, "DANES"); //habla 80m a 0.15€/m
     this->contratos[6] = new ContratoTP(45999000, f3, 400); //habla 400m (300m a 10€, exceso 0.15€/m)
     this->ncon=7;
}

void Empresa::ver() const {
    // Mostrar el número de clientes y contratos
    cout << "La Empresa tiene " << ncli << " clientes y " << ncon << " contratos\n";

    // Mostrar la lista de clientes
    cout << "Clientes:\n";
    for (int i = 0; i < ncli; ++i) {
        cout << *clientes[i] << "\n";
    }

    // Mostrar la lista de contratos
    cout << "Contratos:\n";
    ContratoTP *tp;
    ContratoMovil *movil;
    for(int i=0; i<ncon; i++){
        if ( tp = dynamic_cast<ContratoTP*>(contratos[i])) {
            cout << *tp << "\n";
        }else if (movil = dynamic_cast<ContratoMovil*>(contratos[i])) {
            cout << *movil << "\n";
        }else{
            cout<< "si";
        }
    }
}
