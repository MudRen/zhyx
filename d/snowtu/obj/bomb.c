#include <ansi.h>
#include <combat.h>
inherit ITEM;

void setup(){ }

void create()
{
set_name(HIR"����"NOR,({"bian pao","pao zhu","pao"}));
set_weight(5000);
if( clonep() )
        set_default_object(__FILE__);
else    {
        set("unit", "��");
        set("long", HIR"����ʱ����ı��񣬵�(dian)�ź�Ҫ�ǵö�(diu)��ȥŶ��\n"NOR);
        set("material", "paper");
        set("value",1000);
        }
setup();
}

int init()
{
//add_action("do_dian", "dian");
//add_action("do_drop", "diu");
}

int do_dian(string arg)
{
object ob = this_object();
object me = environment(ob);
if ( !arg || !id(arg) )
        return notify_fail("��Ҫ��ʲô��\n");
if ( ob->query("burn") )
        return notify_fail("�Ѿ������ˣ�"HIR"����ž�� =^-^=\n"NOR);
if ( me->is_busy() )
        return notify_fail("����æ���ء�\n");

message_vision("$N��������ͳ���$n���û���������...\n"NOR,me,ob);
me->start_busy(1);
ob->set("burn",1);
ob->set("num",1+random(6));
ob->save();
call_out("check",1,ob);
return 1;
}

int do_drop(string arg)
{
object ob = this_object();
object me = environment(ob);
if ( !arg || !id(arg) )
        return notify_fail("��Ҫ��ʲô��\n");
if ( me->is_busy() )
        return notify_fail("����æ���ء�\n");
if (ob->query("burn") == 1)
{
message_vision("$N����$nսս�����ģ����ɽ�$n���˳�ȥ...\n"NOR,me,ob);
me->start_busy(1);
ob->move(environment(me));
call_out("dismiss",60,ob);
return 1;
}
else {
return notify_fail("û�����Ҫ�Ӱ���\n");
}
}

void dismiss(object ob)
{
if ( !ob ) return;
if ( living(environment(ob)) ) return;
message("vision","һ���������Ĺ���������"+ob->name()+"����ϲ���Խ�������������....\n",environment(ob),ob);
destruct(ob);
return;
}

void check(object ob)
{
int num;
string msg;
object who = environment(ob);
if ( !ob || !who )
        return;
message("vision",YEL+ob->name()+YEL"�Ļ�ҩ������ֱ��....\n"NOR,who,ob);
ob->add("num",-1);
ob->save();
if ( num=ob->query("num")<=0 )
        {
        msg = YEL"���䡱��һ����"+ob->name()+YEL"ը�����ˣ��ڰ��������������ɫ��\n\n
               |
           \   *  ./
          .  * * * .
         -=*  POP! *=-              
         .  .* * *  .
          /    *  .\
               |  
               .     

������/\~~~~~~~~~~~~~\������������^*^���������$$�� .�� 
����./��\~~~��~�� ~~~~\ ������ʥ�� .���֡� *�� $����$�� * 
����/ ^^ \ �T�T�T�T�T�T\.�������� *��*����*�� $���﨎$�� * 
��..��[]������� �� |������ .����������*�� $��������$�� * 
��&&�������������� ��'|'�� @��������������* $����������$ * 
�� �����������������������{�z�y�xԸ��ʥ�����֦��||��� \n"NOR;
        msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL);
        msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL);
        msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL);
        msg = replace_string(msg,"ʥ",NOR HIY"ʥ"NOR YEL);
        msg = replace_string(msg,"��",NOR HIY"��"NOR YEL);
        msg = replace_string(msg,"��",NOR HIY"��"NOR YEL);
        msg = replace_string(msg,"��",NOR HIY"��"NOR YEL);
        msg = replace_string(msg,"��",NOR HIG"��"NOR YEL);
        msg = replace_string(msg,"��",NOR HIG"��"NOR YEL);
        msg = replace_string(msg,"��",NOR HIR"��"NOR YEL);
        msg = replace_string(msg,"��",NOR HIG"��"NOR YEL);
        msg = replace_string(msg,"��",NOR HIR"��"NOR YEL);
        msg = replace_string(msg,"��",NOR BLINK HIY"��"NOR YEL);
        msg = replace_string(msg,"HIG",HIG);
        msg = replace_string(msg,"HIC",HIC);
        msg = replace_string(msg,"HIY",HIY);
        message("vision",msg,environment(ob),ob);
        if ( living(environment(ob)) )
                {
                message("vision",HIR"����������ը����"+environment(ob)->name()+"�������ˣ���ը�˸����ţ�\n"NOR,environment(ob),ob);
                num = 40+random(100);
                }
        destruct(ob);
        }
else    {
        remove_call_out("check");
        call_out("check",1,ob);
        }
return;
}


