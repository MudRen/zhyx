inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "���붴");
        set("long",
"����������붴��һֻ�������̾�������������˽���������\n"
"һ������޺�Ȼ��㷢���˹�������˵���ػ����۰��������ı��ء�\n"
"�пյĻ�������(search)һ�»�������ջ�\n"
);
        set("exits", ([ 
              "south" : __DIR__"dong5", 
           ]));
        set("objects", ([ 
             __DIR__"npc/huoqilin" : 1,
          ]));        
        setup();
} 

void init()
{
     add_action ("do_search","search"); 
     add_action ("do_train","train");
}

int do_train(string arg)
{
    write("���붴��Ķ������ޣ�����Ҳ��ѱ������\n");
    return 1;
} 

int do_search (string arg)
{
    object who = this_player();   
    object tu;  
 
   
   if ( who->query("reborn_start/qilindong/tu") )
   {
         write("���Ѿ��ҵ���ͼ����!\n");
         return 1;
   }

   if (random(10))
   {
      message_vision ("$N�Ĵ�������һ����ʲôҲû���ҵ���\n",who);
      write("������������ϸ����!\n");  
      who->start_busy(2 + random(2));
   }
   else
   {
      tu = new(__DIR__"npc/obj/tu");
      message_vision ("\nͻȻֻ��$N���ӿ���Ҷ���ҳ�һ��"+YEL"���Ƶ�ͼ��"NOR+"��\n",who);
     
      tu->move(who);  
      who->set("reborn_start/qilindong/tu",1);
      message("vision", HIW"��ת�����š�����˵"+ who->query("name") +
                       "�����붴���ҵ���һ�Ų��Ƶ�ͼ����\n"NOR, users());
      
  }
  return 1;
}


