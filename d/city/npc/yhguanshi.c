

#include <ansi.h>
#include <login.h> 
inherit NPC;


void create()
{
     //  reload("guanshi");
       set_name("��ʦ��", ({"guanshi","guan shi"}));
       set("gender", "����");
       set("title", HIC"���й���"NOR);
       set("combat_exp", 100000);
       set("age", 26);
       set("per", 24);
       set("attitude", "friendly");
       set("long","��ʦ��ԭ������˫ȫ���������ֺʹ��ƹ���̫�ڵ�����г����\n���Եò�����͢�����á�����������������ʶ����Ϊ���й��¡�\n");
       set("shen_type", 1);
      
       set("max_qi", 1100);
       set("max_jing", 1100);
       set("qi", 1100);
       set("jing", 1100);
       set("neili", 2300);
       set("max_neili", 1200);
       set("jiali", 80);
       set("max_jingli", 1200);
       set("jingli", 2300);
       set("combat_exp", 800000);

       set_skill("literate", 500);
       set_skill("unarmed", 500);
       set_skill("dodge", 500);
       set_skill("parry", 500);

       
       setup();


}

void init()
{
        object ob;

        ::init();
        set("chat_chance", 12);
        set("inquiry", ([
                "name" : "���²��ţ�������ʦ����",
                "here" : "�����������ջ������ѩ������Ǳ�����С�\n",
                "dvunix" : "���ǹ����书��Ȼ���Ǻܺã������������ѱ����£�������֪���ֵ��ĸ�������ȥ�����ˡ����������������ڼҡ�\n",
                "������ѩ" : "���ǹ����书��Ȼ���Ǻܺã������������ѱ����£�������֪���ֵ��ĸ�������ȥ�����ˡ����������������ڼҡ�\n",
                "����" : "���ǹ����书��Ȼ���Ǻܺã������������ѱ����£�������֪���ֵ��ĸ�������ȥ�����ˡ����������������ڼҡ�\n",
                "xueer" : "�����������ں���Ъ���أ�",
                "ѩ��" : "�����������ں���Ъ���أ�",
                "������" : "�����������ں���Ъ���أ�",
   ]) );

        set("chat_msg", ({
                "��ʦ������˵��������ү��ύ�����ˡ�\n",   
                "��ʦ���������´������㼸�ۡ�\n",
                "��ʦ������˵�������ܵ����������ܶ඼�����ǹ��ӵ����ѡ�\n",
                "��ʦ������˵�������ϵ����Ѷ����������үһЩ���档���Ժ������������ҡ�\n",
                "��ʦ��������˵������������Ŷ���ӣ�����˵�����˲�������������϶��������졣\n"
                
       }) );
      
    ob = this_player();
    ::init();
    if (userp(ob))
    if(random(10)>3)
       remove_call_out("greeting");
       call_out("greeting", 1, ob);
}

void accept_kill(object me)
{       

        me->add("daoluan",1);
        command("sigh2");
        command("chat ��������");
          
        me->add("daoluan",1);
        me->save();
        return;

}

void greeting(object ob)
{
if( !ob || environment(ob) != environment() ) return;
if(!userp(ob)) return;
message_vision( "$N��$n��ȭ����.\n\n",this_object(),ob );
if(ob->query("id")=="dvunix")
  {
          command("say �ޣ�"+ob->query("name")+"����,�������ˡ�");
  }
else
  {
command("say ��λ" + RANK_D->query_respect(ob)
+ "����Ҫ��ȥð�գ���������Ǳ�ܰɣ�\n");
if (ob->query("gender") == "����"||ob->query("gender") == "����")
    {
        command("say "+"��λ" + RANK_D->query_respect(ob)+"����ӭ���п���������");
        command("xixi");
    }
else
    {
        command("say ƽ�����������������⣬�������ȴ����һλ" + RANK_D->query_respect(ob)+"\n");
        command("say �������±��ӵ��Ҹ������ˣ�\n"); 
        command("grin");
    }
  }
}

