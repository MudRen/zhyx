#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("�󻹵�", ({ "dan" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","���Ƶ�һ�Ľ�Ʒ �÷���boost\n");
                set("unit", "��");
                set("value", 5000000);
                set("no_drop",1);
        }
        setup();
}

int query_autoload() { return 1; }
void init()
{
  if(this_player()==environment())
  add_action("boost_skill","boost");
}

int boost_skill()
{
        object ob, *list, couple_ob;
        string theskill;
        int thelevel = 0;
        mapping skl, lrn, map;
        string *sname, *mapped,target,cardname;
        int i, marry_flag;
        ob = this_player();
        skl = ob->query_skills();
        if(!sizeof(skl)) {
                write( "��Ŀǰ��û��ѧ���κμ��ܡ�\n");
                return 1;
        }
        sname  = sort_array( keys(skl), (: strcmp :) );

        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        lrn = ob->query_learned();
        if( !mapp(lrn) ) lrn = ([]);

       for(i=0; i<sizeof(skl); i++) {
                if(skl[sname[i]] > thelevel) {theskill = sname[i]; thelevel = skl[sname[i]];} 
        }
        ob->set_skill(theskill, (int)thelevel+1);
message_vision("$N��"+to_chinese(theskill)+"��ǿ�ˡ�\n", this_player());
destruct(this_object());
return 1;
}

