inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "С����");
        set("long",
"[1;32m����һ�����ص�Сľ�ݣ����еİ��趼��Щ�򵥱�Ҫ�ļҾ�\n"
"��������һ��С�����������һЩʳ�һ���������Ů����������æµ\n"
"��ʲô��\n"
); 
        set("objects", ([ 
            "/quest/tulong/npc/spiritgirl" : 1,
            "/quest/tulong/npc/kid" : 1,
          ]));        
        set("exits", ([ /* sizeof() == 4 */
           "east" : "/d/tulong/village",
   ]));

        setup();
//        replace_program(ROOM);

}

void init()
{
  add_action ("do_search","search"); 
}

int do_search (string arg)
{
  object who = this_player ();
  object where = this_object ();
  object hook;
 
        if (  present("hook", who) ) {
                return notify_fail("�㲻���Ѿ��ҵ�����\n");
          }
  if (random(10))
  {
    message_vision ("$N�Ĵ�������һ����ʲôҲû���ҵ���\n",who);  
  }
  else
  {
    hook = new ("/quest/tulong/obj/hook");
    message_vision ("$N��С�ݵĴ�С���䶼���˸��飬������һ��С���ӣ�\n",who,hook);
    hook->move(who);  
  }
  return 1;
}

