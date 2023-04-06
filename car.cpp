#include<iostream>
#include<windows.h>
#include<conio.h>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;
void login()
{
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t       CAR RENTAL SYSTEM \n\n";
    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t     LOGIN \n";
    cout << "\t\t\t\t\t------------------------------\n\n";
    cout << "\t\t\t\t\tEnter Password: ";
    int key_no;
    string pass="";
    cin>>pass;
    while(key_no!=10)
    {
        key_no=cin.get();
        if(pass=="pass")
        {
            system("Color 0A");
            cout<<"\n\n\n\t\t\t\t\tLOADING \n\t\t\t\t\t";
            for(int i=0;i<8;i++)
            {
                Sleep(500);
		        cout << "...";
            }
            cout << "\n\n\n\t\t\t\t\tAccess Granted!! \n\n\n";
            system("CLS");
        }
        else
        {
            cout << "\nAccess Aborted...\n";
            login();
        }
    }
}

//globle
struct Date
{
  int d, m, y;
};
const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int countLeapYears(Date d)
{
  int years = d.y;
  if (d.m <= 2)
    years--;
  return years / 4 - years / 100 + years / 400;
}
int getDifference(Date dt1, Date dt2)
{
  long int n1 = dt1.y * 365 + dt1.d;
  for (int i = 0; i < dt1.m - 1; i++)
    n1 += monthDays[i];
  n1 += countLeapYears(dt1);
  long int n2 = dt2.y * 365 + dt2.d;
  for (int i = 0; i < dt2.m - 1; i++)
    n2 += monthDays[i];
  n2 += countLeapYears(dt2);
  return (n2 - n1);
}
int isContractDaysExceeded(int customerRentDate, int todaysDate, int customerRentDays)
{

  int d1, m1, y1, d2, m2, y2, temp3;
  d1 = customerRentDate / 1000000;
  temp3 = customerRentDate % 1000000;
  m1 = temp3 / 10000;
  y1 = temp3 % 10000;

  d2 = todaysDate / 1000000;
  temp3 = todaysDate % 1000000;
  m2 = temp3 / 10000;
  y2 = temp3 % 10000;

  Date dt1 = {d1, m1, y1};
  Date dt2 = {d2, m2, y2};

  temp3 = getDifference(dt1, dt2);
  if (temp3 > customerRentDays)
  {
    return temp3;
  }
  else
  {
    return 0;
  }
}

class Customer;
class CarData;
class Rent;

class Customer
{
protected:
    string customerName;
    string carModel;
    string carNumber;
    string phone_no;
    string adhaar_no;
    int rentDate = 0;
    int rentDays = 0;
    int isValidNumber = 0; //for Phone Number Validation
    int isValidAdhaar = 0; //for adhaar validation

public:

    void takeCustomerData()
    {
        fflush(stdin);
        system("PAUSE");
        system("CLS");

        cout<< "\t\t\t\t\t------------------------------";
        cout<< "\n\t\t\t\t\t\t     CUSTOMER DATA \n";
        cout<< "\t\t\t\t\t------------------------------\n\n";

        cout<<endl<<"\t\t\t\tPlease Enter your Name: ";
        getline(cin, customerName);
        cout <<endl<<"\t\t\t\tPlease Enter your Phone Number: ";
        cin >> phone_no;
        cout <<endl<< "\t\t\t\tPlease Enter your Adhaar Number: ";
        cin >> adhaar_no;

        if (phone_no.length() == 10)
        {
            for (int i = 0; i < 10; i++)
            {
                if (!isdigit(phone_no[i]))
                {
                    isValidNumber = 1;
                    break;
                }
            }
        }
        else
        {
            isValidNumber = 1;
        }

        //isValidNumber = 0;
        //isValidAdhaar = 0;

        //Validation of Adhaar Number
        if (adhaar_no.length() == 12)
        {
            if (adhaar_no[0] == 1 || adhaar_no[0] == 0)
            {
                isValidAdhaar = 1;
            }
            for (int i = 0; i < 12; i++)
            {
                if (!isdigit(adhaar_no[i]))
                {
                    isValidAdhaar = 1;
                    break;
                }
            }
        }
        else
        {
            isValidAdhaar = 1;
        }

        //validation msg
        if (isValidNumber == 1 && isValidAdhaar == 1)
        {
            cout << "\n\n\t\t\tYou have Entered Invalid Phone Number And Adhaar Number." << endl;
            cout << "\t\t\tPlease ! Insert Valid Information!!" << endl;

            system("PAUSE");
            system("CLS");

            takeCustomerData();
        }
        else if (isValidNumber == 1)
        {
            cout << "\n\n\t\t\tYou have Entered Invalid Phone Number." << endl;
            cout << "\t\t\tPlease ! Insert Valid Information!!" << endl;

            system("PAUSE");
            system("CLS");

            takeCustomerData();
        }
        else if (isValidAdhaar == 1)
        {
            cout << "\t\t\tYou have Entered Invalid Adhaar Number" << endl;
            cout << "\t\t\tPlease ! Insert Valid Information!!" << endl;

            system("PAUSE");
            system("CLS");

            takeCustomerData();
        }

    }

    //showallcustomerhistory

    void showAllCustomers()
    {
        system("PAUSE");
        system("CLS");
        cout << "\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t\t     ALL CUSTOMERS\n";
        cout << "\t\t\t\t\t------------------------------\n\n";

        ifstream fin;
        fin.open("allCustomerHistory.txt");
        string line;

        while (!fin.eof())
        {

            getline(fin, line, ',');
            //cout<<"line size  "<<line.size()<<"\n";
            if (line.size() != 0)
            {
                cout << "\n\t\t\t-----------------------";
                cout << "\n\t\t\t\t  " << line << "\n";
                cout << "\t\t\t-----------------------\n\n";

                getline(fin, line, ',');
                cout << "Car Model                "<< "\t\t\t\t" << line << "\n";

                getline(fin, line, ',');
                cout << "Car Number               "<< "\t\t\t\t" << line << "\n";

                getline(fin, line, ',');
                cout << "Phone Number             "<< "\t\t\t\t" << line << "\n";

                getline(fin, line, ',');
                cout << "Adhaar Number            "<< "\t\t\t\t" << line << "\n";

                getline(fin, line, ',');
                cout << "Date of Rent             "<< "\t\t\t\t" << line << "\n";

                getline(fin, line);
                cout << "Contract Days            "<< "\t\t\t\t" << line << "\n";
            }
        }

        fin.close();
    }
    //no of customer
    int totalCustomers()
    {
        ifstream fin;
        int noOfCustomers = 0;
        fin.open("customers.txt");
        string line;
        while (!fin.eof())
        {
            getline(fin, line);
            if (line.size() > 0)
            noOfCustomers++;
        }
        fin.close();
        return noOfCustomers;
    }
};


//cardata class
class CarData
{
protected:
    string carName;
    int seatingCapacity, chargingTime, range;
    float power, batteryCapacity;
    int ratePerKm, stocks;

public:
    void showAllCars()
    {
        ifstream fin;
        fin.open("allCar.txt");
        string line;
        char carSrNo = 'A';
        while (!fin.eof())
        {
            getline(fin, line, ',');
            if (line.size() != 0)
            {
                cout << carSrNo << ") ------->" << line << "\n";
                getline(fin, line);
                carSrNo++;
            }
        }
        fin.close();
    }

    char carChoice;
    void addNewCar()
    {
        fflush(stdin);
        system("PAUSE");
        system("CLS");
        cout << "\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t\t    ADD NEW CAR\n";
        cout << "\t\t\t\t\t------------------------------\n\n";

        cout << "Enter following specifications of car\n";
        cout << "Car Name             : ";
        fflush(stdin);
        getline(cin,carName);
        cout << "Power                : ";
        cin >> power;
        cout << "Battery Capacity     : ";
        cin >> batteryCapacity;
        cout << "Range                : ";
        cin >> range;
        cout << "Charging Time        : ";
        cin >> chargingTime;
        cout << "Seating Capacity     : ";
        cin >> seatingCapacity;
        cout << "Car rate per KM      : ";
        cin >> ratePerKm;
        cout << "Car stock            : ";
        cin >> stocks;
        ostringstream strg;
        strg<< power;
        string s1 = strg.str();
         ostringstream strg1;
        strg1<< batteryCapacity;
        string s2 = strg1.str();
         ostringstream strg2;
        strg2<< range;
        string s3 = strg2.str();
         ostringstream strg3;
        strg3<< chargingTime;
        string s4 = strg3.str();
         ostringstream strg4;
        strg4<< seatingCapacity;
        string s5 = strg4.str();
         ostringstream strg5;
        strg5<< ratePerKm;
        string s6 = strg5.str();
         ostringstream strg6;
        strg6<< stocks;
        string s7 = strg6.str();

    //adding this new car information in file
        ofstream fout;
        fout.open("allCar.txt", ios::app);

        string line;
        line = carName + ", " + s1 + "bhp, " + s2 + "kWh, " + s3 + "km, " + s4 + "Min(0-80%), " + s5 + ", " + "$" + s6 + "/KM, " + s7;
        fout << endl<< line;
        fout.close();
    }

    void deleteCar()
    {
        do
        {
            system("PAUSE");
            system("CLS");
            cout << "\t\t\t\t\t------------------------------";
            cout << "\n\t\t\t\t\t\t     DELETE CAR\n";
            cout << "\t\t\t\t\t------------------------------\n\n";
            showAllCars();

            cout << endl;
            cout << "\t\t\t\tChoose a Car from the above options: ";
            carChoice = getche();
            cout << endl;

            string line;
            char carSrNo = 'A';

            if (!(carChoice <= 'A' + totalCars() && carChoice >= 'A' || carChoice <= 'a' + totalCars() && carChoice >= 'a'))
                cout << "Invaild Car choice. Please try again!" << endl;
            else
            {
                ifstream fin;
                ofstream fout;

                fin.open("allCar.txt");
                fout.open("temp.txt");

                while (!fin.eof())
                {
                    getline(fin, line);
                    if (carChoice == carSrNo || carChoice == carSrNo + 32)
                    {
                        //DELETING choosed car
                        cout << "\n\nCar has been deleted";
                    }
                    else
                    {
                        if (line.size() != 0)
                        fout << line << endl;
                    }
                    carSrNo++;
                }
                fin.close();
                fout.close();
                remove("allCar.txt");
                rename("temp.txt", "allCar.txt");
            }
        } while (!(carChoice <= 'A' + totalCars() && carChoice >= 'A' || carChoice <= 'a' + totalCars() && carChoice >= 'a'));
    }

    void modifyCarData()
    {
        do
        {
            system("PAUSE");
            system("CLS");
            cout << "\t\t\t\t\t------------------------------";
            cout << "\n\t\t\t\t\t\t     MODIFY CAR\n";
            cout << "\t\t\t\t\t------------------------------\n\n";
            showAllCars();

            cout << endl;
            cout << "\t\t\t\tChoose a Car from the above options: ";
            carChoice = getche();
            cout << endl;

            ifstream fin;
            ofstream fout;

            fin.open("allCar.txt");
            fout.open("temp.txt");
            string line;
            char carSrNo = 'A';

            if (!(carChoice <= 'A' + totalCars() && carChoice >= 'A' || carChoice <= 'a' + totalCars() && carChoice >= 'a'))
                cout << "Invaild Car Model. Please try again!" << endl;
            else
            {
                while (!fin.eof())
                {
                    getline(fin, line);
                    if (carChoice == carSrNo || carChoice == carSrNo + 32)
                    {
                    //modifying choosed car

                        cout << "Enter following specifications of car\n";
                        cout << "Car Name             : ";
                        fflush(stdin);
                        getline(cin,carName);
                        cout << "Power                : ";
                        cin >> power;
                        cout << "Battery Capacity     : ";
                        cin >> batteryCapacity;
                        cout << "Range                : ";
                        cin >> range;
                        cout << "Charging Time        : ";
                        cin >> chargingTime;
                        cout << "Seating Capacity     : ";
                        cin >> seatingCapacity;
                        cout << "Car rate per KM      : ";
                        cin >> ratePerKm;
                        cout << "Car stock            : ";
                        cin >> stocks;
                        ostringstream strg;
                        strg<< power;
                        string s1 = strg.str();
                        ostringstream stg;
                        stg<< batteryCapacity;
                        string s2 = stg.str();
                        ostringstream strg1;
                        strg1<< range;
                        string s3 = strg1.str();
                        ostringstream strg2;
                        strg2<< chargingTime;
                        string s4 = strg2.str();
                        ostringstream strg3;
                        strg3<< seatingCapacity;
                        string s5 = strg3.str();
                        ostringstream strg4;
                        strg4<< ratePerKm;
                        string s6 = strg4.str();
                        ostringstream strg5;
                        strg5<< stocks;
                        string s7 = strg5.str();

                        line = carName + ", " + s1 + "bhp, " + s2 + "kWh, " + s3 + "km, " + s4 + "Min(0-80%), " + s5 + ", " + "$" + s6 + "/KM, " + s7;
                        fout << line << endl;

                        cout << "\nCar has been modified";
                    }
                    else
                    {
                        if (line.size() != 0)
                            fout << line << endl;
                    }
                    carSrNo++;
                }
                fin.close();
                fout.close();

                remove("allCar.txt");
                rename("temp.txt", "allCar.txt");
            }

        } while (!(carChoice <= 'A' + totalCars() && carChoice >= 'A' || carChoice <= 'a' + totalCars() && carChoice >= 'a'));
    }


     int totalCars()
    {
        ifstream fin;
        int noOfCars = 0;
        fin.open("allCar.txt");
        string line;
        while (!fin.eof())
        {
            getline(fin, line);
            noOfCars++;
        }
        fin.close();
        return noOfCars;
    }
    int readCarRate(string carName)
    {
        int carRate;

        ifstream fin;
        fin.open("allCar.txt");
        string line;
        char carSrNo = 'A';
        while (!fin.eof())
        {
            getline(fin, line, ',');
            if (line.size() != 0)
            {
                if (line.compare(carName))
                {
                    for (int i = 4; i >= 0; i--)
                    {
                        getline(fin, line, ',');
                    }
                    stringstream geek(line);
                    int x = 0;
                    geek >> x;
                    carRate = x;
                    break;
                }
                getline(fin, line);
                carSrNo++;
            }
        }
        fin.close();
        return carRate;
    }

};


//Handle car
class Rent:public Customer,public CarData
{
private:
    int rentalfee = 0;
    char carChoice;
public:
    void customersCarInfo()
  {
    do
    {
      system("PAUSE");
      system("CLS");
      cout << "\t\t\t\t\t------------------------------";
      cout << "\n\t\t\t\t\t\t     CAR OPTIONS\n";
      cout << "\t\t\t\t\t------------------------------\n\n";
      showAllCars();

      cout << endl;
      cout << "\t\t\t\tChoose a Car from the above options: ";
      carChoice = getche();
      cout << endl;

      system("PAUSE");
      system("CLS");

      ifstream fin;
      fin.open("allCar.txt");
      string line;
      stringstream templine;
      char carSrNo = 'A';
      while (!fin.eof())
      {
        getline(fin, line, ',');
        carModel = line;
        if (carChoice == carSrNo || carChoice == carSrNo + 32)
        {
          carModel = line;

          cout << "\t\t\t\t\t------------------------------";
          cout << "\n\t\t\t\t\t\t  " << line << "\n";
          cout << "\t\t\t\t\t------------------------------\n\n";
          cout << "Specification\n\n";

          //reading power
          getline(fin, line, ',');
          cout << "Power           "
               << "\t\t\t\t" << line << "\n";

          //reading battery capacity
          getline(fin, line, ',');
          cout << "Battery Capacity"
               << "\t\t\t\t" << line << "\n";

          //reading Range
          getline(fin, line, ',');
          cout << "Range           "
               << "\t\t\t\t" << line << "\n";

          //reading Charging Time
          getline(fin, line, ',');
          cout << "Charging Time   "
               << "\t\t\t\t" << line << "\n";

          //reading Seating Capacity
          getline(fin, line, ',');
          cout << "Seating Capacity"
               << "\t\t\t\t" << line << "\n";

          //reading Seating Capacity
          getline(fin, line, ',');
          cout << "rate per KM     "
               << "\t\t\t\t" << line << "\n";
          templine << line;
          templine >> ratePerKm;

          //reading Seating Capacity
          getline(fin, line, ',');
          cout << "Available Stock "
               << "\t\t\t\t" << line << "\n";
          templine << line;
          templine >> stocks;

          carChoice = carSrNo;
          break;
        }
        getline(fin, line);
        carSrNo++;
      }
      fin.close();

      if (carChoice >= 'A' + totalCars())
        cout << "Invaild Car Model. Please try again!\n";

      if (stocks == 0)
        cout << "Sorry! this car is out of stocks choose any other car\n";

    } while (carChoice >= 'A' + totalCars() && stocks == 0);

    cout << "\n\nPlease provide following information: " << endl;

    cout << "Please select a Car No. : ";
    cin >> carNumber;
    cout << "Number of days you wish to rent the car : ";
    cin >> rentDays;
    cout << "Enter rent date (informat ddmmyyyy): ";
    cin >> rentDate;
    cout << endl;

    calculateRent();
  }

  void calculateRent()
  {
    Sleep(1);
    system("CLS");
    cout << "Calculating rent. Please wait......" << endl;
    Sleep(2);
    rentalfee = rentDays * 149;

    rentInvoice();
  }

  void rentInvoice()
  {
    cout << "\n\t\t                       Car Rental - Customer Invoice                  " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	| Invoice No. :"
         << "----------------------|" << setw(25) << "#Cnb81353"
         << " |" << endl;
    cout << "\t\t	| Customer Name:"
         << "---------------------|" << setw(25) << customerName << " |" << endl;
    cout << "\t\t	| Car Model :"
         << "------------------------|" << setw(25) << carModel << " |" << endl;
    cout << "\t\t	| Car No. :"
         << "--------------------------|" << setw(25) << carNumber << " |" << endl;
    cout << "\t\t	| Number of rentDays :"
         << "---------------|" << setw(25) << rentDays << " |" << endl;
    cout << "\t\t	| Your Rental Amount is :"
         << "------------|" << setw(25) << "Rs." << rentalfee << " |" << endl;
    cout << "\t\t	| Caution Money :"
         << "--------------------|" << setw(25) << "Rs.50"
         << " |" << endl;
    cout << "\t\t	| Advanced :"
         << "-------------------------|" << setw(25) << "Rs.40"
         << " |" << endl;
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\n";
    cout << "\t\t	| Total Rental Amount is :"
         << "-----------|" << setw(25) << "Rs." << rentalfee + 50 + 40 << " |" << endl;
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\t\t	 # This is a computer generated invoce and it does not" << endl;
    cout << "\t\t	 require an authorised signture #" << endl;
    cout << " " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	You are advised to pay up the amount before due date." << endl;
    cout << "\t\t	Otherwise penelty fee will be applied" << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;

    system("PAUSE");
    system("CLS");

    //adding this customer information in file
    ofstream fout, foutAllCustomerHistory;
    fout.open("customers.txt", ios::app);
    foutAllCustomerHistory.open("allCustomerHistory.txt", ios::app);
    ostringstream strg;
    strg<< rentDate;
    string s1 = strg.str();
    ostringstream stg;
    stg<< rentDays;
    string s2 = stg.str();

    string line;
    line = customerName + ", " + carModel + ", " + carNumber + ", " + phone_no + ", " + adhaar_no + ", " + s1 + ", " + s2;
    fout << endl
         << line;
    foutAllCustomerHistory << endl
                           << line;
    foutAllCustomerHistory.close();
    fout.close();
  }


  void takeBackCar()
  {
    Rent customer[totalCustomers()];

    ifstream fin;
    ofstream fout;

    fin.open("customers.txt");
    string line;
    //stringstream templine;
    int customerSrNo = 0;

    while (!fin.eof())
    {
        getline(fin, line, ',');
        customer[customerSrNo].customerName = line;

        getline(fin, line, ',');
        customer[customerSrNo].carModel = line;

        getline(fin, line, ',');
        customer[customerSrNo].carNumber = line;

        getline(fin, line, ',');
        customer[customerSrNo].phone_no = line;

        getline(fin, line, ',');
        customer[customerSrNo].adhaar_no = line;

        getline(fin, line, ',');
        stringstream geek(line);
        int x = 0;
        geek >> x;
        customer[customerSrNo].rentDate = x;
        getline(fin, line);
        stringstream g(line);
        int y = 0;
        g >> y;
        customer[customerSrNo].rentDays = y;

        customerSrNo++;
    }
    fin.close();

    int isCustomer = 0;
    string name;

    do
    {
        system("PAUSE");
        system("CLS");
        cout << "\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t\t    TAKE BACK CAR\n";
        cout << "\t\t\t\t\t------------------------------\n\n";

        cout << "Enter customer's name : ";
        cin>>name;

        for (customerSrNo = 0; customerSrNo < totalCustomers(); customerSrNo++)
        {
            if (!name.compare(customer[customerSrNo].customerName))
            {
                isCustomer = customerSrNo + 1;
                break;
            }
        }

        if (!isCustomer)
        cout << "there is no customer with name : " << name << " Please try again!" << endl;
    } while (!isCustomer);

  //taking some data before taking car like km used, todays date

    int KM, todaysDate, penaltyAmount = 0, penaltyDays = 0, totalAmountDue = 0;
    int prePaidAmount = 90;
    cout << "Enter KM used       : ";
    cin >> KM;
    cout << "enter todays date   : ";
    cin >> todaysDate;
    penaltyDays = isContractDaysExceeded(customer[isCustomer - 1].rentDate, todaysDate, customer[isCustomer - 1].rentDays);

    if (penaltyDays > 0)
    {
        penaltyAmount = penaltyDays * (49 + 149);
    }

    totalAmountDue = (readCarRate(customer[isCustomer - 1].carModel)) * KM;
    totalAmountDue += penaltyAmount;
    totalAmountDue -= prePaidAmount;

    fout.open("temp.txt");

    for (customerSrNo = 0; customerSrNo < totalCustomers(); customerSrNo++)
    {
        if ((name.compare(customer[customerSrNo].customerName)))//return 0 if compare and return
        {
            ostringstream strg;
            strg<< customer[customerSrNo].rentDate;
            string s1 = strg.str();
            strg<< customer[customerSrNo].rentDays;
            string s2 = strg.str();
            line = customer[customerSrNo].customerName + ", " + customer[customerSrNo].carModel + ", " + customer[customerSrNo].carNumber + ", " + customer[customerSrNo].phone_no + ", " + customer[customerSrNo].adhaar_no + ", " + s1 + ", " + s2;
            if (customerSrNo == 0)
            {
                fout << line;
            }
            else
            {
                fout << endl<< line;
            }
        }
    }

    fout.close();
    remove("customers.txt");
    rename("temp.txt", "customers.txt");

  ////////// HERE INVOICE///////////////
    cout << "\n\t\t                       Car Rental - Customer Invoice                  " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	| Invoice No. :"
       << "----------------------------------|" << setw(25) << "#CxRb8353"
       << " |" << endl;
    cout << "\t\t	| Customer Name:"
       << "---------------------------------|" << setw(25) << customer[isCustomer - 1].customerName << " |" << endl;
    cout << "\t\t	| Car Model :"
       << "------------------------------------|" << setw(25) << customer[isCustomer - 1].carModel << " |" << endl;
    cout << "\t\t	| Car No. :"
       << "--------------------------------------|" << setw(25) << customer[isCustomer - 1].carNumber << " |" << endl;
    cout << "\t\t	| Rent Date. :"
       << "-----------------------------------|" << setw(25) << customer[isCustomer - 1].rentDate << " |" << endl;
    cout << "\t\t	| Todays Date. :"
       << "---------------------------------|" << setw(25) << todaysDate << " |" << endl;
    cout << "\t\t	| Amount of "<<KM<<"KM used Car :"
       << "----------------------|" << setw(23) << "Rs." << (readCarRate(customer[isCustomer - 1].carModel)) * KM << " |" << endl;
    cout << "\t\t	| Penalty Amount :"
       << "-------------------------------|" << setw(25) << penaltyAmount
       << " |" << endl;
    cout << "\t\t	| Caution Money paid on rent date:"
       << "---------------|" << setw(25) << "Rs.50"
       << " |" << endl;
    cout << "\t\t	| Advanced paid on rent date:"
       << "--------------------|" << setw(25) << "Rs.40"
       << " |" << endl;
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\n";
    if (totalAmountDue > 0)
    {
        cout << "\t\t	| Total Amount to pay :"
         << "-------|" << setw(10) << "Rs." << totalAmountDue << " |" << endl;
    }
    else
    {
        cout << "\t\t	| Total Amount refunded :"
         << "-------|" << setw(10) << "Rs." << -1*(totalAmountDue) << " |" << endl;
    }
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\t\t	 # This is a computer generated invoce and it does not" << endl;
    cout << "\t\t	 require an authorised signture #" << endl;
    cout << " " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	 THANKYOU FOR USING OUR CAR RENTAL SERVICE " << endl;
    cout << "\t\t	Otherwise penelty fee will be applied" << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;

    system("PAUSE");
    system("CLS");

    cout << "\n Car taken back succesfully ";
}
void showDefaulterCustomers()
{
  Rent customer[totalCustomers()];

  system("PAUSE");
  system("CLS");
  cout << "\t\t\t\t\t------------------------------";
  cout << "\n\t\t\t\t\t\t     DEFAULTER CUSTOMERS\n";
  cout << "\t\t\t\t\t------------------------------\n\n";

  ifstream fin;

  fin.open("customers.txt");
  string line;
  int customerSrNo = 0;

  while (!fin.eof())
  {
    getline(fin, line, ',');
    customer[customerSrNo].customerName = line;

    getline(fin, line, ',');
    customer[customerSrNo].carModel = line;

    getline(fin, line, ',');
    customer[customerSrNo].carNumber = line;

    getline(fin, line, ',');
    customer[customerSrNo].phone_no = line;

    getline(fin, line, ',');
    customer[customerSrNo].adhaar_no = line;

    getline(fin, line, ',');
    stringstream geek(line);
    int x = 0;
    geek >> x;
    customer[customerSrNo].rentDate = x;
    getline(fin, line);
     stringstream g(line);
    int y = 0;
    g >> y;
    customer[customerSrNo].rentDays = y;
    customerSrNo++;
  }

  fin.close();

  int todaysDate;

  cout << "Enter todays date in format dd/mm/yyyy : ";
  cin >> todaysDate;

  for (customerSrNo = 0; customerSrNo < totalCustomers(); customerSrNo++)
  {

    if (isContractDaysExceeded(customer[customerSrNo].rentDate, todaysDate, customer[customerSrNo].rentDays))//return days
    {
      cout << "\n\t\t\t-----------------------";
      cout << "\n\t\t\t " << customer[customerSrNo].customerName << "\n";
      cout << "\t\t\t-----------------------\n\n";

      cout << "Car Model                "
           << "\t\t\t\t" << customer[customerSrNo].carModel << "\n";

      cout << "Car Number               "
           << "\t\t\t\t" << customer[customerSrNo].carNumber << "\n";

      cout << "Phone Number             "
           << "\t\t\t\t" << customer[customerSrNo].phone_no << "\n";

      cout << "Adhaar Number            "
           << "\t\t\t\t" << customer[customerSrNo].adhaar_no << "\n";

      cout << "Date of Rent             "
           << "\t\t\t\t" << customer[customerSrNo].rentDate << "\n";

      cout << "Contract Days            "
           << "\t\t\t\t" << customer[customerSrNo].rentDays << "\n";
    }
  }
}

};



//homescreene

void handlecar1();
void homescreen()
{
    Rent rent;
    while(1)
    {
        system("CLS");
        cout << "\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t\t     CAR OPTIONS\n";
        cout << "\t\t\t\t\t------------------------------\n\n";
        cout << "choose any one option\n\n";
        cout << "1) Rent Car\n"
        << "2) Handle Cars\n"
        << "3) Customer details\n"
        << "4) Get Back Car from Customer\n"
        << "5) Customers that Haven't given Car Back Yet\n"
        << "0) to exit\n";
        cout<<"\n enter choice:";
        int ch;
        cin>>ch;
        switch(ch)
        {
                case 0:
                    	system("CLS");
                        cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t>>>>>>>>>>>>>>>>>> THANK YOU <<<<<<<<<<<<<<<<<<\n\n ";
                        Sleep(10);
                        exit(1);
                        break;
                case 1:
                        Sleep(1);
                        rent.takeCustomerData();
                        rent.customersCarInfo();
                        cout << "\n\nPress any key to go to homescreen \n";
                        getch();
                        break;
                case 2: handlecar1();
                        break;
                case 3:
                        system("CLS");
                        rent.showAllCustomers();
                        cout << "\n\nPress any key to go to homescreen \n";
                        getch();
                        break;
                case 4: system("CLS");
                            rent.takeBackCar();
                            cout << "\n\nPress any key to go to homescreen \n";
                            getch();

                            break;
                case 5:
                            system("CLS");
                            rent.showDefaulterCustomers();
                            cout << "\n\nPress any key to go to homescreen \n";
                            getch();
                            break;
                default:
                        cout<<"\n Sorry! Invalid Option! \n";
                        getch();
                        break;
                }
    }
}


void handlecar1()
{
    CarData gg;
    while(1)
    {
        system("CLS");

        cout << "\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t\t     HANDLE CARS\n";
        cout << "\t\t\t\t\t------------------------------\n\n";
        cout << "choose any one option\n\n";
        cout << "1) Add New Car\n"
           << "2) Modify Existing Cars\n"
           << "3) Delete Existing Cars\n"
           << "4) View All Cars\n"
           <<"\nENTER   0:   To Exit     ";
        cout<<"\n enter choice:";
        int c;
        cin>>c;
        switch(c)
        {

            case 0: homescreen();
                    break;
            case 1:
                        gg.addNewCar();
                        cout << "\n\nPress any key to go to homescreen \n";
                        break;
                    case 2:

                         gg.modifyCarData();
                         cout << "\n\nPress any key to go to homescreen \n";
                         getch();
                         break;
                    case 3:
                        gg.deleteCar();
                        cout << "\n\nPress any key to go to homescreen \n";
                        getch();
                        break;
                    case 4: system("CLS");
                            cout << "\t\t\t\t\t------------------------------";
                            cout << "\n\t\t\t\t\t\t     ALL CARS\n";
                            cout << "\t\t\t\t\t------------------------------\n\n";
                            gg.showAllCars();
                            cout << "\n\nPress any key to go to homescreen \n";
                            getch();
                            break;
                    default:
                        cout<<"\n Sorry! Invalid Option! \n";
                        getch();
                        break;
        }
    }
}
int main()
{
  login();
  homescreen();
}
