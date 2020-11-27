object get_object(string name)
{
        object ob;
        if( ob=find_object(name) )
                return ob;
        return load_object(name);
}
