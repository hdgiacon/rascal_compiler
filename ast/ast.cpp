// codigo de ast

#include <string>


class A_Programa{
    public:
        string id;
        A_Bloco bloco;

        A_Programa(string _id, A_Bloco _bloco){
            id = _id
            bloco = _bloco
        }


}


class A_Bloco{
    public:
        A_LstDecSub secDecSub;
        A_LstDecVar secDecVar;
        A_CmdComp cmdComp;
}