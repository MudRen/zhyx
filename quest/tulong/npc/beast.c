inherit NPC;

void create()
{
  set_name("������", ({"beast"}));
  set("gender", "����");
  set("age", 10);
  set("long","���˵������˼���γɵĹ����ޣ����ס�˵Ļ��ǡ�\n");
  set("attitude", "aggressive");
  set("combat_exp", 51100000);
  set("max_qi",9000);
  set("max_jing",9000);
  set("max_neili",9000);
  set("jiali",100); 
  set_temp("apply/damage", 250);
  set_temp("apply/armor", 200);
  setup();
}

void die ()
{
  object me = this_object();
  object where = environment (me);

  message_vision ("\n$N������ȥ����Ϊһ�����̡�\n",me);  
  if (! present("beast 4",where) &&
      where->query("short")=="����")
  {
    object ob = new ("/quest/tulong/npc/beast");
    ob->move(where);
    message_vision ("\nͻȻ���������ֳ���һֻ�����ޣ�\n",me);   
  }
  destruct (me);  
}

void unconcious ()
{
  die();
}

