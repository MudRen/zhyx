// story:lonely ��ɷ����

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

nosave mixed *story = ({
        "�����,ŦԼ,����Ů����֮�ߡ���",
        "��Ӣ�����޵еľ����ѽ�β������",
        "������޵�һ���������ڵ�һʽ�����в������Ѱѻ�Ӣ�۵ġ�����������ѹ�¡�",
        "��Ӣ���ջسལ����������������������Ѫ���������¡���",
        "�޵У����ӵĵ��в���������˫�����䶨�ˣ�",
        "��Ӣ�ۣ��һ�δ�����ܡ��޵У��������һʽ�л������ɣ�",
        "�޵У����������������������Һ�?",
        "��Ӣ�ۣ����л�������һʽ���ǡ��������������⡱�����ڻ��ͨ���ɵĿ������С�",
        "��Ӣ�ۣ���������ɷ���ǣ��¼�һ����ʹ���ɡ�",
        "�޵У�������ͷ�����Բ��ѣ������ɣ�",
        "��Ӣ��һ��ŭ�ȣ����ƺ���ལ�������ལ��̻���һ��������������޵����ɹ�ȥ��",
        "¡������Ӣ��˫���ѻ����޵����ϡ��޵���Ѫ�ɳ����⡣",
        "�Ĵ�һƬ�¼ţ�Ψ�����ڵ��ϵ��޵������������Ұ��ˡ��Ұ��ˡ�Ϊʲô�㲻ɱ�ҡ���",
        "��Ӣ�������������ˡ�������ˡ�������ˡ�����",
        "Ȼ����ɷ�������к������أ�",
        "ɱ����ô���ˡ�ѹ������ô����顭��������ô�õĹ¼š��������ֻʣ������Щ��",
        "��һ�����У�Ψ�������µ�һ��������",
        "��Ӣ�����쳤̾���찡��Ϊ��ƫƫ���ң��ѵ���ע��ҪΪ�����µ�һ���������¼�һ����",
        "��ۣ�����������Ӣ������ɷ���ǵ���̫�ã����ܲ���ѹ������������ȥҪ��������ˣ�",
        "��ۣ����ˣ�����ȥ�½���Ѱ������ѡ�����滪Ӣ����ɷ����֮λ",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return CYN "����ɷ���ǡ�" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob;
        string msg;
        mapping my;
        int select;

        select = 0;
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                               //  environment($1)->query("outdoors") &&
                                                 ! $1->query("special_skill/emperor") &&
                                                 ! $1->query("special_skill/lonely") &&
                                                 ! $1->query("special_skill/queen") &&
                                                 ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];

        if (random( 5200 -  ob->query("kar") * 100 ) > 0 )
        {
                msg = HIC "��ۣ�" + ob->name(1) +
                      HIC "������ã������������̫����ʺϽ�����ɷ����֮λ��" NOR;
                ob->add("kar", 1+random(2));
                if ( ob->query("kar") >= 50 ) ob->set("kar",50);


        } else
        {
                msg = HIY "��ۣ�������" + ob->name(1) +
                      HIY "����ȷʵ���Խ�����ɷ����֮λ��" NOR;
                ob->set("special_skill/lonely", 1);
                ob->delete("family");
                ob->delete("class");
                log_file("static/tianzi", sprintf("%s(%s) �����ɷ�������� at %s.\n",
                         ob->name(1), ob->query("id"), ctime(time())));
                select = 1;

        }
        remove_call_out("announce");
        call_out("announce",1,select,ob);
        return msg;
}

void announce(int select, object ob)
{
      if (select == 0 )
      CHANNEL_D->do_channel(this_object(), "rumor",
         "��˵Ŀǰ�Ҳ���������ѡ������ɷ����֮λ,��" + ob->name() + "����۶��ݼ��˸�Ե��\n");
      else
      CHANNEL_D->do_channel(this_object(), "rumor",
           "��˵" + ob->name() + "�����ѡ�У����λ�Ӣ�۳�Ϊ��һ����ɷ���ǡ�\n");
}
