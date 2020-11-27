inherit ITEM;


void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("���굤", ({"huanhun dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�źں�����ҩ�衣\n");
        }
}
int do_eat(string arg)
{
        string *skills;
        mapping all_skills;
        int i;
        if (! id(arg))
             return notify_fail("��Ҫ��ʲôҩ��\n");
        else
        {
                all_skills = this_player()->query_skills();
                if (! sizeof(all_skills))  
                        destruct(this_object());
                skills = keys(all_skills);
                for (i = 0; i < sizeof(skills); i++)
                this_player()->set_skill(skills[i], all_skills[skills[i]] + 2);
                this_player()->add("combat_exp", this_player()->query("combat_exp") / 40);
                this_player()->add("potential", this_player()->query("potential") - 
                                   this_player()->query("learned_points"));
                message_vision("$N����һ�Ż��굤,�Ӱ��޳�����������С��������\n", this_player());
                log_file("static/EAT_DAN",
                         sprintf("%s �����˷������Ļػ굤 %s\n", this_player()->query("id"), ctime(time())) );
                destruct(this_object());
                return 1;
        }
}




