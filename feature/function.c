//clone from es2
#include <ansi.h>
int set_function(string key,int lv)
{
        this_player()->set("functions/"+key+"/level",lv);
        return 1;
}
int query_function(string key)
{
    if(this_player())
        return this_player()->query("functions/"+key+"/level");
    else
    return 0;
}
int function_improved(string key,int point)
{
    if(!this_player()) return 0;
        this_player()->add("functions/"+key+"/learned",point);
        if(this_player()->query("functions/"+key+"/learned")>=this_player()->query("functions/"+key+"/level")*this_player()->query("functions/"+key+"/level")*10)
        {
                this_player()->add("functions/"+key+"/level",1);
                this_player()->set("functions/"+key+"/learned",0);
                tell_object(this_player(),HIY);
               tell_object(this_player(),"��Ĺ�������һ�㡣\n" NOR);
        }
        return 1;
}

int delete_function(string key)
{
        return this_player()->delete("functions/"+key);
}

