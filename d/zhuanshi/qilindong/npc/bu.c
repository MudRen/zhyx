#include <ansi.h>
inherit NPC;
int ask_jian();
int ask_baojian();
void consider();
void create()
{
    set_name("������", ({"bu jingyun", "bu", "jingyun"}));
    set("nickname", HIY "��������" NOR );
    set("gender", "����");
    set("age", 25);
    set("long",
        "���������»��������������ƣ��������˳ơ��������񡹡�\n");
    set("attitude", "peaceful");

    set("str", 100);
    set("int", 80);
    set("con", 86);
    set("dex", 240);
    set("chat_chance", 1);
    set("chat_msg", ({
        "������̾�˿����������� ���� �ҵ���������ȥ�� ������\n",
        "�����Ƶ�ͷ��˼����Ȼ���\n",
    }));
    set("inquiry", ([
        "����"     : "˭�ܰ����ҵ����ƣ���ʲô�¶���Ӧ��! \n",
        "����" : (: ask_baojian:),
        "�����ý�" : (: ask_baojian:),
    ]));
    set("qi", 20000);
   set("max_qi", 20000);
    set("jing", 5000);
    set("max_jing", 5000);
    set("max_jingli", 3000);

    set("jingli", 3000);
    set("neili", 6000);
    set("max_neili", 20000);
    set("jiali", 300);

     set("combat_exp", 60000000);

  set_skill("force", 600);
    set_skill("huntian-baojian", 600);
     set_skill("paiyun-zhang", 300);
   set_skill("strike", 500);
     set_skill("dodge", 500);
    set_skill("zhuangzi-wu", 500);
    set_skill("parry", 500);
   set_skill("sword", 500);
    set_skill("zhuihun-jian", 500);
    set_skill("qimen-wuxing",800);
    set_skill("literate",550);           // ����ʶ��
    map_skill("force"  , "huntian-baojian");
    map_skill("strike", "paiyun-zhang");
    map_skill("dodge"  , "zhuangzi-wu");
    map_skill("parry"  , "paiyun-zhang");
             prepare_skill("strike" , "paiyun-zhang"); 
    create_family("���»�", 2, "����");
         set("chat_chance_combat", 150);
            set("chat_msg_combat", ({ 
                    (: perform_action, "strike.paishan" :), 
            })); 


	setup();

    carry_object("/d/taohua/obj/bupao")->wear();


}

int accept_object(object who, object ob)
{

    if ( (string) ob->query("id") =="ling pai" ) {
        // �Ƿ��ǽ��ı���
        if(ob->query("owner") == who->query("id") )
        {
            if (!(int)who->query_temp("tmark/ling")) who->set_temp("tmark/ling", 0);
            message_vision("�����ƿ��˿�$N���������ƣ����˵�ͷ��˵����\n"
                                   "�ѵ��㽫�����ͻء������ҵĶ����Ҿ������ˡ�\n"
                                   "��Ϊ����,�ҿ��Ը���������ܡ�\n", who);
           who->set_temp("tmark/ling", 1);
            return 1;
        }
    }
}

int ask_baojian()
{
  int p1, p2;
  if ((int)this_player()->query("_passwd")) {
 say("�����Ʋ��õ�˵�����Ҳ��Ƕ������������Ҳ�֪����\n");
  }
if ((int)this_player()->query_temp("tmark/ling")) {
 say("������һ����˵��������ô֪���ģ�\n");
 write("�����ƶ�һ�٣����Ŷ������˵�����Ҿ͸���������");
// p1=random(4)+1;
// p2=random(4)+1;

    p1 = random(100)+1;
    this_player()->set("_passwd", p1);
    write(CHINESE_D->chinese_number(p1));
    write("��\n���������Ǿ���������\n");
  }
  else {
   message("vision",
   HIY "�����Ʋ�Ȼ��ŭ���ȵ�����Ҳ�����ҵľ������������Ҹ���ƴ�ˣ�\n"
   NOR, environment(), this_object() );
   kill_ob(this_player());
  }
  this_player()->delete_temp("tmark/ling");
  return 1;
}

int ask_jian()
{
  int p1, p2;
            object me,obj;
            me = this_player();
                if (me->query("tmark/ling")) {
 say("������һ����Ц�����ӣ�˵����ƾʲô�����㣿\n");
  }

    if ((int)this_player()->query("_passwd")) {
        say("������һ����˵��������ô֪���ģ����������ܾ���֪����\n");
        write("�����������µ���˵���ðɣ���������ҹ����Ҿ͸����㣺");

        //p2=(int)p1/10;
        // ����p1û�г�ʼ������������p2��p1����Ϊ0

        write(CHINESE_D->chinese_number(p1)+"ʮ"+CHINESE_D->chinese_number(p2));
        write("��\n���������Ǿ����ý�����ֻҪ���롰press ***�����У�\n");
                 me->delete("tmark/ling");
                 me->set("tmark/ling",1);
                me->start_busy(2);
                return 1;
    }
}
