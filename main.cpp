#include <iostream>
#include <iomanip>

using namespace std;

void expandMatrix(float** &matrix, int &weeks, int products) {
    weeks++;
    float** newMatrix = new float*[products];
    for (int i = 0; i < products; ++i) {
        newMatrix[i] = new float[weeks];
        for (int j = 0; j < weeks - 1; ++j) {
            newMatrix[i][j] = matrix[i][j];
        }
        newMatrix[i][weeks - 1] = 0;  
    }
    for (int i = 0; i < products; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = newMatrix;
}

void modifyProduction(float** matrix, int product, int week, float quantity) {
    matrix[product][week] = quantity;
}

float calculateCOGS(float** matrix, float* cost, int products, int week) {
    float cogs = 0;
    for (int i = 0; i < products; ++i) {
        cogs += matrix[i][week] * cost[i];
    }
    return cogs;
}

void calculateMaterialConsumption(float** matrix, int* requirements, float* material, int products, int week) {
    float totalConsumption[4] = {0};  

    for (int i = 0; i < products; ++i) {
        for (int j = 0; j < 4; ++j) {
            totalConsumption[j] += matrix[i][week] * requirements[i * 4 + j];
        }
    }

    cout << "--- Consumo de Materia Prima (Semana " << week + 1 << ") ---" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << "MP-" << i + 1 << ": " << totalConsumption[i] << " unidades" << endl;
    }
}

void calculateFinalInventory(float* inventory, float* material, int products, float* consumption) {
    cout << "--- Inventario Final ---" << endl;
    for (int i = 0; i < 4; ++i) {
        inventory[i] = inventory[i] - consumption[i];
        cout << "MP-" << i + 1 << ": " << inventory[i] * material[i] << endl;
    }
}

int main() {
    int products = 5;  
    int weeks = 4; 

    float** productionPlan = new float*[products];
    for (int i = 0; i < products; ++i) {
        productionPlan[i] = new float[weeks]();
    }

    float cost[] = {10, 12, 8, 15, 9};  

    float material[] = {1000, 800, 1200, 1500};  
    int requirements[] = {
        2, 3, 1, 5,  
        3, 2, 1, 4,  
        1, 2, 3, 4,  
        4, 5, 1, 2,  
        2, 1, 4, 3   
    };

    int option;
    while (true) {
        cout << "--- Sistema de Planificación y Costos (COGS) ---" << endl;
        cout << "1. Ver Plan de Producción" << endl;
        cout << "2. Agregar Nueva Semana" << endl;
        cout << "3. Modificar Producción" << endl;
        cout << "4. Calcular COGS y Inventario Final" << endl;
        cout << "5. Salir" << endl;
        cout << "Opción seleccionada: ";
        cin >> option;

        if (option == 1) {
            cout << "--- Plan de Producción ---" << endl;
            for (int i = 0; i < products; ++i) {
                cout << "Producto " << i + 1 << ": ";
                for (int j = 0; j < weeks; ++j) {
                    cout << productionPlan[i][j] << " ";
                }
                cout << endl;
            }
        } else if (option == 2) {
        	
            expandMatrix(productionPlan, weeks, products);
            cout << "Semana añadida. La matriz ahora tiene " << weeks << " semanas." << endl;
        } else if (option == 3) {
        	
            int product, week;
            float quantity;
            cout << "Ingrese Producto (0-4): ";
            cin >> product;
            cout << "Ingrese Semana (0-4): ";
            cin >> week;
            cout << "Cantidad a producir: ";
            cin >> quantity;
            modifyProduction(productionPlan, product, week, quantity);
        } else if (option == 4) {
            int week;
            cout << "Ingrese Semana para el cálculo de costos: ";
            cin >> week;
            float cogs = calculateCOGS(productionPlan, cost, products, week);
            cout << "--- Reporte de Costos (Semana " << week + 1 << ") ---" << endl;
            cout << "Costo Total de Producción (COGS): $" << cogs << endl;
            calculateMaterialConsumption(productionPlan, requirements, material, products, week);
            calculateFinalInventory(material, cost, products, material);
        } else if (option == 5) {
            for (int i = 0; i < products; ++i) {
                delete[] productionPlan[i];
            }
            delete[] productionPlan;
            cout << "Sistema cerrado." << endl;
            break;
        }
    }

    return 0;
}

