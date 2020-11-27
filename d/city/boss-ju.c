// liumang.c ��å
#include <ansi.h>

inherit NPC;

#define PLACE "yz"     //����
#define TYPE  "bad"    //�ڵ�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��

string *fail_xc_msg1=({
        "place��鿴��û�У�",
        "����û�п�һ��place��",
        "�ѵ�place�Ͳ���Ѳ���ˣ�",
        "ȥplace�ٿ�����",
        "����place�����°���",
        "place��һ������Ҫ�ĵط������ܲ��鿴һ�£�",
        "��û��ȥѲ��place�ɣ�",
});

string *fail_xc_msg2=({
        "������ʲôѲ�ǣ�",
        "����ͻ����ˣ�",
        "Ѳ����ô������ô���ʰ���",
        "��Ҫ������͵����",
        "�������Ҳ̫�������˰ɡ�",
        "��Ҳ����Ѳ�ǰ��������ϵĹܲ������ˣ�",
        "��͵����",
        "������Ҫ̤̤ʵʵ��",
});

mapping bang_bad = ([
        "name" : "С����",
        "id"   : "xdh",
        "place": "yz",
        "boss" : "���ϴ�",
]);

void create()
{
	set_name("���ϴ�", ({ "ju laoda", "laoda" }));
	set("gender", "����");
	set("age", 23);
	set("long", "����һ�����ú�Ӣ�������ӣ�����ȥ�������Σ������޷��������ͱ��ǵ�ͷ��" + bang_bad["name"] + "�����졣\n");
	set("title",HIW"����С����������"NOR);
       set("nickname",HIY"���µ�һ��ɫ��"NOR);
       set("per",29);
	set("combat_exp", 1000000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver",2);
}

void init()
{
       add_action("do_join","join");
       add_action("do_disengage","disengage");
       add_action("do_choose","choose");
       add_action("do_giveup","giveup");
}

int do_join()
{
       string msg;
       object me,obj;
       me = this_player();
       obj = this_object();

       if (me->query("bang_bad"))
       {
               if (me->query("bang_bad/name") == bang_bad["name"])
               {
                       if (me->query("shen") > 0)
                       {
                               message_vision("$N����$n��Ȼ��ŭ������������ӣ�û��ƫƫҪȥð��ʲô���˾��ӣ�\n",obj,me);
                               me->delete("bang_bad");
                               msg = "��˵" + me->name(1) + "��" + obj->name(1) + "�����" + bang_bad["name"];
                               CHANNEL_D->do_channel(this_object(), "rumor", msg);
                               return notify_fail("�㱻" + obj->name() + "��������" + bang_bad["name"] + "��\n");
                       }
                       return notify_fail("���Ѿ�����" + me->query("bang_bad/name") + "�ĳ�Ա�ˣ���ͷ�ˣ�\n");
               }
               return notify_fail("��������" + me->query("bang_bad/name") + "�ĳ�Ա��Ҫ������" + bang_bad["name"] + "����������(disengage)ԭ���İ�ᡣ\n");
       }
       
       if (me->query("bang_good") || me->query("shen") > 0)
       {
               message_vision("$N�������µ���ϸ������$n����ɫԽ��Խ�ѿ���\n",obj,me);
               command("say " + "����������������ʿ�ĵ�����������ʲô�����Ҳ��ӣ�");
               return notify_fail("����" + obj->name() + "������ӭ�㣡\n");
       }

       if (me->query("combat_exp") < 10000)
       {
               command("joke " + me->query("id"));
               command("say ��λ" + RANK_D->query_respect(me) + "���㻹̫���˵㣬�ȶ�������Ȼ���ٳ������һ졣");
               return notify_fail("����" + obj->name() + "������ʵ��̫���˵㡣\n");
       }

       if (me->query("combat_exp") >= 600000)
       {
               command("joke " + me->query("id"));
               command("say ��λ" + RANK_D->query_respect(me) + "����������ô���ˣ�������С���������ס�㡣");
               return notify_fail("����" + obj->name() + "������ȼ�̫���ˡ�\n");
       }

       me->set("bang_bad",bang_bad);
       message_vision("$N��ϥ���£�����$n���������ĺ��������ϴ�\n",me,obj);
       message_vision("$N΢΢һЦ������$n���˵�ͷ��������$nվ��������\n",obj,me);
       tell_object(me,"��ϲ���Ϊ" + bang_bad["name"] + "�ĳ�Ա��\n");
       msg = "��˵" + me->name(1) + "��" + obj->name(1) + "Ϊ�ϴ󣬼�����" + bang_bad["name"];
       CHANNEL_D->do_channel(this_object(), "rumor", msg);
       return 1;
}

int do_disengage()
{
       string msg;
       object me,obj;
       me = this_player();
       obj = this_object();

       if (me->query("bang_good"))
       {
               message_vision("$N�������µ���ϸ������$n����ɫԽ��Խ�ѿ���\n",obj,me);
               command("say " + "����������������ʿ�ĵ�����������ʲô�����Ҳ��ӣ�");
               return notify_fail("����" + obj->name() + "������ӭ�㣡\n");
       }

       if (!me->query("bang_bad") || me->query("bang_bad/name") != bang_bad["name"])
       {
               command("yi " + me->query("id"));
               command("say ��λ" + RANK_D->query_respect(me) + "���㲢����" + bang_bad["name"] + "�ĳ�Ա����");
               return notify_fail("����" + obj->name() + "��������ͷ��ˮ��\n");
       }

       if (me->query("bang_bad/boss") != bang_bad["boss"])
               return notify_fail("��������С���᣿����Ľ�����" + me->query("bang_bad/boss") + "ȥ�ɡ�\n");

       me->delete("bang_bad");

       if (me->query("shen") > 0)
       {
               message_vision("$N����$n��Ȼ��ŭ������������ӣ�û��ƫƫҪȥð��ʲô���˾��ӣ�\n",obj,me);
               me->delete("bang_bad");
               tell_object(me,"�㱻" + obj->name() + "��������" + bang_bad["name"] + "��\n");
               msg = "��˵" + me->name(1) + "��" + obj->name(1) + "�����" + bang_bad["name"];
               CHANNEL_D->do_channel(this_object(), "rumor", msg);
       } else
       {
               message_vision("$N����$n̾���������֪���㲻��������С�ط���һ���ӵģ�Ҳ�գ����Լ����أ�\n",obj,me);
               me->delete("bang_bad");
               tell_object(me,"���������" + bang_bad["name"] + "��\n");
       }
       return 1;
}

int do_choose(string bh)
{
       string msg;
       mapping bang_quest;
       object me,obj;

       me = this_player();
       obj = this_object();

       //����ǰ׵��ģ��͸���
       if (me->query("bang_good"))
       {
               message_vision("$N�������µ���ϸ������$n����ɫԽ��Խ�ѿ���\n",obj,me);
               command("say " + "����������������ʿ�ĵ�����������ʲô�����Ҳ��ӣ�");
               return notify_fail("����" + obj->name() + "������ӭ�㣡\n");
       }

       //������Ǳ����ģ�������ȡ����
       if (!me->query("bang_bad") || me->query("bang_bad/name") != bang_bad["name"])
       {
               command("yi " + me->query("id"));
               command("say ��λ" + RANK_D->query_respect(me) + "���㲢����" + bang_bad["name"] + "�ĳ�Ա����");
               return notify_fail("����" + obj->name() + "��������ͷ��ˮ��\n");
       }

       //����Ǳ���ᣬ���Ǳ����������ô����Ǳ�����¼�ĳ�Ա�����俪�������򣬽������
       if (me->query("shen") > 0)
       {
               message_vision("$N����$n��Ȼ��ŭ������������ӣ�û��ƫƫҪȥð��ʲô���˾��ӣ�\n",obj,me);
               if (me->query("bang_bad/boss") == bang_bad["boss"])
               {
                       message_vision("$N����$nŭ�ȵ�����������" + bang_bad["name"] + "��ǽ���Ц����\n",obj,me);
                       me->delete("bang_quest");
                       me->delete("bang_bad");
                       msg = "��˵" + me->name(1) + "��" + obj->name(1) + "�����" + bang_bad["name"];
                       CHANNEL_D->do_channel(this_object(), "rumor", msg);
                       return notify_fail("�㱻" + obj->name() + "��������" + bang_bad["name"] + "��\n");
               } else
               {
                       message_vision("$N����$nŭ�ȣ��������ҿ����\n",obj,me);
                       return notify_fail("��û�д�" + obj->name() + "������ȡ���κ����񣬷�������һ�ٳ��\n");
               }
       }

       //����Ѿ�������������ʹ��һ��
       if (me->query("bang_quest"))
               return notify_fail(obj->name() + "�����Ŀ�����˵����ղ��������û����ɣ���ʲô��\n");

       //���û�������ţ�����ʾָ��
       if (!bh)
               return notify_fail(obj->name() + "��ֵĿ����㣬������ȡʲô����ָ���ǣ�choose <���>��\n");
 
       //�����׷ɱ��������Ҫ��ȡ����
       if (bh[0..1] == "zs")
               return notify_fail(obj->name() + "΢΢һЦ����Ȼ��׷ɱ�������ȡ���񣿸Ͻ�ȥ��ɰɣ�\n");

       //�����Ѳ�ǣ�������Ƿ����ı��ذ��
       if (bh == "xc" && me->query("bang_bad/place") != bang_bad["place"])
               return notify_fail(obj->name() + "������˰���˵��Ѳ���������飬�ұ��ǵ��ֵܾͿ���ʤ�Σ����������ˣ�\n");

       //������NPC��BUSY���򲻸�����
       if (obj->is_busy())
               return notify_fail(obj->name() + "��æ���أ�����΢��һ�¡�\n");

       //��������Ҹշ�����������Ҫ�ȴ�
       if (time() - me->query("last_bang_quest") < me->query("need_wait_time"))
               return notify_fail("��ɲ��������Ⱥú÷�ʡһ�£�Ȼ��������ȡ����\n");

       //���ñ�ŵ������Ƿ����
       bang_quest = PARTY_QUEST_D->query_city_quest(PLACE,TYPE,bh);

       if (!bang_quest)
               return notify_fail(obj->name() + "�������ӿ��˿�������˵��Ŀǰû��" + bh + "�������\n");

       //�����Ѳ���������鵱���Ƿ��Ѿ�������Ѳ��
       if (bang_quest["id"] == "xc" && !bang_quest["enable"])
               return notify_fail(obj->name() + "΢΢Ц��˵�������Ѿ����ֵ�ȥѲ���ˣ���͵ȸ���ɣ�\n");

       //�����񣬲��ҽ���������б���ɾ�� 
       obj->start_busy(1);
       PARTY_QUEST_D->delete_city_quest(PLACE,TYPE,bh);
       me->set("bang_quest",bang_quest);
       message_vision("$N����$n���˵�ͷ����ô�������ͽ������ˣ��ú�ȥ�ɣ�\n",obj,me);
       tell_object(me,"��ӵ������ǣ�\n" + bang_quest["msg"] + "\n");
       return 1;
}

int do_giveup()
{
       string msg;
       object me,obj;

       me = this_player();
       obj = this_object();

       //����ǰ׵��ģ��͸���
       if (me->query("bang_good"))
       {
               message_vision("$N�������µ���ϸ������$n����ɫԽ��Խ�ѿ���\n",obj,me);
               command("say " + "����������������ʿ�ĵ�����������ʲô�����Ҳ��ӣ�");
               return notify_fail("����" + obj->name() + "������ӭ�㣡\n");
       }

       //������Ǳ����ģ������
       if (!me->query("bang_bad") || me->query("bang_bad/name") != bang_bad["name"])
       {
               command("yi " + me->query("id"));
               command("say ��λ" + RANK_D->query_respect(me) + "���㲢����" + bang_bad["name"] + "�ĳ�Ա����");
               return notify_fail("����" + obj->name() + "��������ͷ��ˮ��\n");
       }

       //����Ǳ���ᣬ���Ǳ����������ô����Ǳ�����¼�ĳ�Ա�����俪�������򣬽������
       if (me->query("shen") > 0)
       {
               message_vision("$N����$n��Ȼ��ŭ������������ӣ�û��ƫƫҪȥð��ʲô���˾��ӣ�\n",obj,me);
               if (me->query("bang_bad/boss") == bang_bad["boss"])
               {
                       message_vision("$N����$nŭ�ȵ�����������" + bang_bad["name"] + "��ǽ���Ц����\n",obj,me);
                       me->delete("bang_quest");
                       me->delete("bang_bad");
                       msg = "��˵" + me->name(1) + "��" + obj->name(1) + "�����" + bang_bad["name"];
                       CHANNEL_D->do_channel(this_object(), "rumor", msg);
                       return notify_fail("�㱻" + obj->name() + "��������" + bang_bad["name"] + "��\n");
               } else
               {
                       message_vision("$N����$nŭ�ȣ��������ҿ����\n",obj,me);
                       return notify_fail("�㱻" + obj->name() + "�ݺݵ�ʹ����һ����\n");
               }
       }

       if (!me->query("bang_quest"))
               return notify_fail(obj->name() + "��ֵĿ�����˵�������ڲ�û�������������ǲ����еķ����ˣ�\n");

       me->delete("bang_quest");
       message_vision("$N����$nһ������̾�����ƺ�������Ϊʲô$nΪ����˵Ĳ��ɲġ�\n",obj,me);
       tell_object(me,obj->name() + "�������һ�ۣ����С���鶼��ɲ��ˣ�һ��ȥ�ú÷�ʡ��ʡ��\n");

       //��¼����ʱ��
       me->set("last_bang_quest",time());

       //������û�������������Ĵ�����¼�����ۼӸ������Ҫ�ȴ���ʱ�䣬���WAIT_TIME�룬���򣬵ȴ�3��
       if (!me->query_temp("finish_bang_times"))
              me->set("need_wait_time",me->query("need_wait_time") + 3);
       else me->set("need_wait_time",3);

       if (me->query("need_wait_time") > WAIT_TIME) me->set("need_wait_time",WAIT_TIME);

       //��������������Ĵ���
       me->delete_temp("finish_bang_times");
       return 1;
}

int accept_object(object who,object me,object ob)
{
       int exp,pot,score,weiwang;
       mapping bang_quest,bonus;
       object env;
       string *place,the_place,msg;

       if (base_name(ob) != "/d/city/npc/obj/yaopai")
               return notify_fail(who->name() + "��м�İ�" + ob->name() + "�׻����㣺ʲô�ö���Ҳ���ң�\n");

       if (!me->query("bang_quest"))
               return notify_fail(who->name() + "������˵�ͷ��û��˵ʲô����\n");

       bang_quest = me->query("bang_quest");

       if (bang_quest["id"] != "xc" || bang_quest["name"] != "Ѳ���ݳ�")      
               return notify_fail(who->name() + "������˵�ͷ��û��˵ʲô����\n");

       place = bang_quest["place"];

       if (sizeof(place))
       {
               the_place = place[random(sizeof(place))];
               env = get_object(the_place);
               msg = fail_xc_msg1[random(sizeof(fail_xc_msg1))];
               msg = replace_string(msg,"place",env->short());
               msg += fail_xc_msg2[random(sizeof(fail_xc_msg2))];
               return notify_fail(who->name() + "�����Ķ���˵��" + msg + "\n");
       }

       message_vision("$N���˵�������$n�ļ�򣺸ɵĺã�\n",who,me);
       exp = bang_quest["bonus"]; 
       pot = exp/(2+random(2)); 
       weiwang = 5 + random(10); 
       score = 5 + random(10); 
       me->delete("bang_quest"); 
       me->add_temp("finish_bang_times",1);
       bonus = ([ "exp" : exp, 
                  "pot" : pot, 
                  "score" : score, 
                  "weiwang" : weiwang, 
                  "prompt": "��Ѳ���ݳǵĹ����У���������" 
               ]);
       QUEST_D->delay_bonus(me, bonus);
       destruct(ob);
       return 1;
}