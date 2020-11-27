#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name("��Ԫ", ({ "dragon soul" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","���������ڵ���������С���������졣�÷���boost\n");
                set("unit", "��");
                set("value", 50000);
                set("no_drop",1);
        }
        setup();
}

void init()
{
  if(this_player()==environment())
  add_action("boost_skill","boost");
}

int boost_skill()
{
        int force_limit, neili_limit, force_skill, add_skill, improve;

        object ob, *list, couple_ob;
        string theskill;
        int thelevel = 0;
        mapping skl, lrn, map;
        string *sname, *mapped,target,cardname;
        int i, marry_flag;
        ob = this_player();
        skl = ob->query_skills(); 

        force_limit = ob->query_skill("force")*10;
        neili_limit = ob->query("max_neili");
        force_skill = ob->query_skill("force", 1); 

        if ( (int)ob->query_condition("putizi_drug" ) > 0 || ob->query("dragon_soul") > 100)
        {
                ob->add("max_neili", -50);
                message_vision(HIR "$N��ͼ������Ԫ����������ܲ��ˣ�����ʵ��䷴��\n" NOR, ob);
                destruct(this_object());
                return 1;
        }
        else if ( neili_limit <= force_limit  )
        {
                ob->add("max_neili", 50);
                ob->add("neili", 50);

                message_vision(HIY "$N�˾�������Ԫ��ֻ��$N��ɫ��������������ԴԴ������\n" NOR, this_player());
                ob->apply_condition("putizi_drug", 1000);
        }        if(!sizeof(skl)) {
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
        ob->add("dragon_soul", 1);
message_vision("$N��"+to_chinese(theskill)+"��ǿ�ˡ�\n", this_player());
destruct(this_object());
return 1;
}

