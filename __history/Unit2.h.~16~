//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

#include <string>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *pg1;
	TTabSheet *tsInfix;
	TTabSheet *txPrefix;
	TTabSheet *tsPostfix;
	TButton *btnInfixToPrefix;
	TButton *btnInfixToPostfix;
	TEdit *editInfix;
	TEdit *editInfixToPrefix;
	TEdit *editInfixToPostfix;
	TComboBox *cbInfixExample;
	TCheckBox *cbPrintStack;
	TCheckBox *cbPrintTracing;
	TRichEdit *reAuthor;
	TPageControl *pg2;
	TTabSheet *tsTracing;
	TTabSheet *tsAuthor;
	TRichEdit *reOutput;
	TLabel *lblInfix;
	TLabel *lblPostfix;
	TEdit *editPostfixToInfix;
	TButton *btnPostfixToInfix;
	TEdit *editPostfix;
	TComboBox *cbPostfixExample;
	TButton *btnPostfixToPrefix;
	TEdit *editPostfixToPrefix;
	TEdit *editPrefix;
	TButton *btnPrefixToInfix;
	TEdit *editPrefixToInfix;
	TComboBox *cbPrefixExample;
	TLabel *lblPrefix;
	TButton *btnPrefixToPostfix;
	TEdit *editPrefixToPostfix;
	TLabel *lbl1;
	TLabel *lbl2;
	TLabel *lbl3;
	void __fastcall cbPrintStackClick(TObject *Sender);
	void __fastcall cbPrintTracingClick(TObject *Sender);
	void __fastcall btnInfixToPrefixClick(TObject *Sender);
	void __fastcall btnInfixToPostfixClick(TObject *Sender);
	void __fastcall btnPrefixToPostfixClick(TObject *Sender);
	void __fastcall btnPrefixToInfixClick(TObject *Sender);
	void __fastcall btnPostfixToPrefixClick(TObject *Sender);
	void __fastcall btnPostfixToInfixClick(TObject *Sender);
	void __fastcall cbInfixExampleSelect(TObject *Sender);
	void __fastcall cbPrefixExampleSelect(TObject *Sender);
	void __fastcall cbPostfixExampleChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);

	void __fastcall AppendTextToOutput(const String &text);

	int __fastcall performOperation(char operation, int operand1, int operand2);

	inline bool __fastcall isOperand(char c);
	inline bool __fastcall isOperator(char c);
	inline int __fastcall precedence(char op);

	inline std::string __fastcall reverseExpression(const std::string& expr);
	std::string __fastcall InfixToPostfix(const std::string& infix);
	std::string __fastcall InfixToPrefix(const std::string& infix);
	std::string __fastcall PostfixToInfix(const std::string& postfix);
	std::string __fastcall PostfixToPrefix(const std::string& postfix);
	std::string __fastcall PrefixToInfix(const std::string& prefix);
	std::string __fastcall PrefixToPostfix(const std::string& prefix);
	int __fastcall evaluatePostfix(const std::string& postfix);
	int __fastcall evaluatePrefix(const std::string& prefix);
	int __fastcall evaluateInfix(const std::string& infix);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
