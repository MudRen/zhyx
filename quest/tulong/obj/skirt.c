#include <armor.h>
#include <ansi.h>

inherit CLOTH;
void check_color(); 
void create()
{
   set_name(YEL "��ɫ����" NOR, ({ "color skirt","skirt" }) );
   set_weight(20);
                set("long", "ȡ�ʺ���ɫ�������������ҹ������֯�ɡ� \n");
     set("material", "silk");
     set("unit", "��");
     set("armor_prop/armor",50 ); 
     set("armor_prop/personality", 20);
     set("female_only", 100);  
   setup();
         call_out("check_color",3);
  }
 
int query_autoload(){ return 1;}

void init()
{
       object me;
       object ob = this_object();
  
       if (!environment(ob)||!interactive(environment(ob))) {
                 return;
                    }
       me = this_player();
       if (!geteuid(me)||geteuid(me)!="night")  {
       tell_object(me,"��ɫ���ѻ�Ϊһ��ѣĿ�Ĺ⻪����ʧ���˿����С�\n");  
                 destruct(ob);
                    } 
      return;
} 

void check_color()
{
     object ob = this_object(); 
  remove_call_out("check_color");
       switch ((int)random(7)) {
           case 0 : 
              ob->set("name",HIG"��ɫ����" NOR);
               break; 
           case 1 : 
              ob->set("name",HIW"��ɫ����" NOR);
               break;
           case 2 :
              ob->set("name",HIR"��ɫ����" NOR);
               break;
           case 3 :
              ob->set("name",HIY"��ɫ����" NOR);
               break;
           case 4 :
              ob->set("name",HIM"��ɫ����" NOR);
               break;
           case 5 :
              ob->set("name",HIC"��ɫ����" NOR);
               break; 
           case 6 :
              ob->set("name",YEL"��ɫ����" NOR);
               break;
           default:
                break;
                   } 
        call_out("check_color",3);
}

