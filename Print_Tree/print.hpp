static void _print_DOT(Tree* tree, FILE* out)
{
    assert(tree!=NULL);

    if(tree)
    {
        fprintf(out, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n",(int)tree, tree->question);

        if(tree->yes)
        {
            fprintf(out, "%d -> %d [color = blue]\n", (int)tree, (int)tree->yes);
            _print_DOT(tree->yes,out);
        }

        if(tree->no)
        {
            fprintf(out, "%d -> %d [color = blue]\n", (int)tree, (int)tree->no);
            _print_DOT(tree->no ,out);
        }
    }
}


void print_DOT(Tree* tree)
{
    FILE* out = fopen("print_DOT", "w");

    assert(out!=NULL);
    fprintf(out, "digraph G{\n");

    _print_DOT(tree, out);

    fprintf(out, "\n}");

    fclose(out);

    system("xdot print_DOT");
}
