#include "MyForm.h"
#include <Windows.h>
#include <cmath>
#include <string>
#include <stdexcept>

using namespace System;
using namespace System::Windows::Forms;

// Custom exception
public ref class CustomException : public Exception
{
public:
    CustomException() : Exception("Custom exception occurred.") {}
};

public ref class GeometricProgressionCalculatorForm : public Form
{
private:
    TextBox^ txtBoxA;
    TextBox^ txtBoxR;
    TextBox^ txtBoxN;
    Button^ btnCalculate;
    Label^ lblResult;

public:
    GeometricProgressionCalculatorForm()
    {
        InitializeComponents();
    }

private:
    void InitializeComponents()
    {
        // Form settings
        this->Text = "Geometric Progression Calculator";
        this->Size = System::Drawing::Size(300, 200);
        this->StartPosition = FormStartPosition::CenterScreen;

        // TextBoxes for parameters
        txtBoxA = gcnew TextBox();
        txtBoxA->Location = System::Drawing::Point(20, 20);
        txtBoxA->Size = System::Drawing::Size(100, 20);
        txtBoxA->Text = "Enter a";
        txtBoxA->ForeColor = System::Drawing::SystemColors::GrayText;
        txtBoxA->Enter += gcnew EventHandler(this, &GeometricProgressionCalculatorForm::TextBox_Enter);
        txtBoxA->Leave += gcnew EventHandler(this, &GeometricProgressionCalculatorForm::TextBox_Leave);

        txtBoxR = gcnew TextBox();
        txtBoxR->Location = System::Drawing::Point(20, 60);
        txtBoxR->Size = System::Drawing::Size(100, 20);
        txtBoxR->Text = "Enter r";
        txtBoxR->ForeColor = System::Drawing::SystemColors::GrayText;
        txtBoxR->Enter += gcnew EventHandler(this, &GeometricProgressionCalculatorForm::TextBox_Enter);
        txtBoxR->Leave += gcnew EventHandler(this, &GeometricProgressionCalculatorForm::TextBox_Leave);

        txtBoxN = gcnew TextBox();
        txtBoxN->Location = System::Drawing::Point(20, 100);
        txtBoxN->Size = System::Drawing::Size(100, 20);
        txtBoxN->Text = "Enter n";
        txtBoxN->ForeColor = System::Drawing::SystemColors::GrayText;
        txtBoxN->Enter += gcnew EventHandler(this, &GeometricProgressionCalculatorForm::TextBox_Enter);
        txtBoxN->Leave += gcnew EventHandler(this, &GeometricProgressionCalculatorForm::TextBox_Leave);

        // Button for calculation
        btnCalculate = gcnew Button();
        btnCalculate->Location = System::Drawing::Point(150, 60);
        btnCalculate->Size = System::Drawing::Size(100, 30);
        btnCalculate->Text = "Calculate";
        btnCalculate->Click += gcnew EventHandler(this, &GeometricProgressionCalculatorForm::CalculateButtonClick);

        // Label for result
        lblResult = gcnew Label();
        lblResult->Location = System::Drawing::Point(150, 100);
        lblResult->Size = System::Drawing::Size(100, 20);
        lblResult->Text = "Result: ";

        // Adding elements to the form
        this->Controls->Add(txtBoxA);
        this->Controls->Add(txtBoxR);
        this->Controls->Add(txtBoxN);
        this->Controls->Add(btnCalculate);
        this->Controls->Add(lblResult);
    }

    // Event handler for clearing text on focus
    void TextBox_Enter(Object^ sender, EventArgs^ e)
    {
        TextBox^ textBox = dynamic_cast<TextBox^>(sender);
        if (textBox != nullptr && textBox->ForeColor == System::Drawing::SystemColors::GrayText)
        {
            textBox->Text = "";
            textBox->ForeColor = System::Drawing::SystemColors::WindowText;
        }
    }

    // Event handler for setting placeholder text if the field is empty
    void TextBox_Leave(Object^ sender, EventArgs^ e)
    {
        TextBox^ textBox = dynamic_cast<TextBox^>(sender);
        if (textBox != nullptr)
        {
            if (String::IsNullOrEmpty(textBox->Text) && textBox->Tag != nullptr)
            {
                textBox->Text = textBox->Tag->ToString();
                textBox->ForeColor = System::Drawing::SystemColors::GrayText;
            }
        }
    }

    // Event handler for the calculation button
    void CalculateButtonClick(Object^ sender, EventArgs^ e)
    {
        try
        {
            // Getting input values
            double a = Convert::ToDouble(txtBoxA->Text);
            double r = Convert::ToDouble(txtBoxR->Text);
            int n = Convert::ToInt32(txtBoxN->Text);

            // Calculating the sum
            double result = CalculateSumWithCustomException(a, r, n);

            // Displaying the result
            lblResult->Text = "Result: " + result.ToString();
        }
        catch (Exception^ ex)
        {
            // Exception handling
            lblResult->Text = "Error: " + ex->Message;
        }
    }

    // Function with custom exception for geometric progression
    double CalculateSumWithCustomException(double a, double r, int n)
    {
        if (n < 0)
            throw gcnew ArgumentOutOfRangeException("n", "Number of terms should be non-negative.");

        double sum = a * (1 - Math::Pow(r, n)) / (1 - r);
        return sum;
    }
};

int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    GeometricProgressionCalculatorForm^ form = gcnew GeometricProgressionCalculatorForm();
    Application::Run(form);

    return 0;
}


