#include <obj/load.h>

int main(int argc, char *argv[])
{
    Model model;
    load_model(&model, "duck.obj");
    print_model_info(&model);
    return 0;
}