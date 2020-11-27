// european.c ������
#include <ansi.h>

inherit NPC;

string *all_jiuming = ({
        "$n�ݺݵظ���$Nһ������ͣ��ɺ����۾���һ��Ҫƴ�������ӡ�\n",
        "$Nһ�Ѿ�ס$n�����죬�����ű��������ĺ�У�$n�ŵû���˵��������\n",
        "$n͵͵��$N�Ժ��������һľ����$N����Ż�ת��ҡҡ�λεĳ�$n��ȥ��\n",
        "$Nһ���߿����ţ����$n������䵹�񵽴����ѡ�\n",
        "$n��$Nһ�����и첲����ŭ���ӣ���ʹ֮�¸��ǲ��ɵĴ����Һ���\n",
        "$nһ·���ܣ���ͼ˦�����׷ɱ�Լ���$N��һ�߳���ɤ�Ӵ󺰡���������\n",
        "$Nɱ�����ڵ����ŵ�Ѫ�ı�����һ���粽�ͳ嵽$n��ǰ����ͷ�����ؿ�����ȥ��\n",
        "$n��$N����һ�ţ�������֧�����·磬���ݽ�ҧ��ŭĿԲ����\n",
        "$N�մ��ſ���ʧ��$n�ʹ����ӵ������������嵽���ھʹ󺰣�������������\n",
        "$N�߾ٱ�������$n��У����������е�Ǯ��ͨͨ���ҽ������������Ҿ�һ�������㣡��\n",
        "$N�����ű���������������������ľͰ�Ǯ�ƶ��������������ҵȷ��ˣ���\n",
        "$n���ſ�ǻ�������У�����������˭���Ⱦ��Ұ�����\n",
        "$N��Ц��һ���ƽ�$n��ɳ�ȥ�������˰����Ȳ������ķ�����Ѱ�Ҳ��\n",
        "$Nһ���߿�$n������̰���ĳ�Ǯ�����˹�ȥ��\n",
        "$Nһ����$n�����ڵأ�����һ���ֽ�һֻ���ǹ����������롣\n",
        "$nһ�߶�����$N�Ĺ�����һ�ߺ��ˣ������������ۿ���֧�Ų�ס�ˡ�\n",
});

string *woman_jiuming = ({
        "$N��Ц�ų�$n˵������а�����а������ƺ���Ҳû�˾ȵ����㣡��\n",
        "$Nһ��§ס$n��ɫ���Ե����µ���������$n�޽е���˻���ߡ�\n",
        "$N������Ц���ƽ�$n��$n�ŵü�������...\n",
        "$N����˫�����´���$n��һ��һ���رƽ���ǰ...\n",
        "$n˫ȭ���裬ƴ������ס$N������һ����ˤ���ڵأ���������������\n",
        "$n��˻���ߵغ��У����������������Ⱦ��Ұ�����\n",
        "$Nһ�����ƽ�$n�鵹�ڵأ���Ц��������ȥ��\n",
        "$N�����������$n������ȥ��$n�ŵô������У��Ĵ�������\n",
});

void random_move();
void destruct_me();
int  is_stay_in_room();
void jiuming(object npc,object enemy);

void create()
{
        set_name("������", ({ "european" }));
        set("long", "һ�������ˡ�\n");
        set("gender", "����");
        set("age", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);
        set("shen", -1000);

        set("combat_exp", 3000000);
        set("scale", 100);

        set_skill("force", 1);
        set_skill("xiyang-neigong", 1);
        set_skill("dodge", 1);
        set_skill("xiyang-boji", 1);
        set_skill("parry", 1);
        set_skill("xiyang-jian", 1);
        set_skill("sword", 1);

        map_skill("sword", "xiyang-jian");
        map_skill("force", "xiyang-neigong");
        map_skill("dodge", "xiyang-boji");
        map_skill("parry", "xiyang-jian");

        set("rank_info/rude", "��ë��");

       set("chat_chance", 30);
       set("chat_msg", ({ (: random_move :) }));
       set("scale", 100);
        set_temp("born_time", time());
        add_money("silver",50);
       keep_heart_beat();
        setup();

       carry_object("/clone/cloth/cloth")->wear();
       carry_object("/clone/weapon/xiyang-sword")->wield();
}

int accept_fight(object ob)
{
        command("say �ܺã����ҾͲ������ˡ�");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say �ߣ�ʲô�ˣ�");
        kill_ob(ob);
        return 1;
}

void random_move()
{
        int all_enemy;
        object env,*inv,npc;

        if (time() - query_temp("born_time") > 600)
        {
                destruct_me();
                return;
        }

        all_enemy = GROUP_QUEST_D->query_enemy() + 1;
        if (all_enemy < 2) all_enemy = 2;

        if (!GROUP_QUEST_D->query_running_quest() &&
            objectp(env = environment(this_object())) &&
            random(all_enemy) == all_enemy/2)
        {
                inv = all_inventory(env);
                inv -= ({ this_object() });
                inv = filter_array(inv, (: living($1) :));
                if (inv)
                        inv = filter_array(inv, (: !userp($1) && $1->query("race") == "����" :));
                if (inv)
                        inv = filter_array(inv, (: strsrch(base_name($1),"/kungfu/class/generate/") == -1 :));
                if (inv)
                        inv = filter_array(inv, (: $1->query("combat_exp") <= 500000 :));
                if (inv)
                        inv = filter_array(inv, (: !$1->query("family") :));
                if (inv && sizeof(inv))
                {
                        npc = inv[random(sizeof(inv))];
                        jiuming(npc,this_object());
                }
                inv = 0;                
        }
        GROUP_QUEST_D->random_move(this_object());
}

void destruct_me()
{
        message_vision("$N����ææ�����ˡ�\n", this_object());
        destruct(this_object());
}

void jiuming(object npc,object enemy)
{
        string msg;

        if (!npc || !enemy)
                return;

        if (npc->query("gender") == "Ů��" && random(2))
                msg = woman_jiuming[random(sizeof(woman_jiuming))];
        else
                msg = all_jiuming[random(sizeof(all_jiuming))];

        msg = replace_string(msg,"$N",enemy->name());
        msg = replace_string(msg,"$n",npc->name());

        message("group_quest",HIR "��������֡�" NOR + WHT + msg + NOR,users());
}
