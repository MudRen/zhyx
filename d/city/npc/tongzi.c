inherit NPC;
string ask_me();
void create()
{
        set_name("�����޵�����", ({ "pu ren", "pu", "ren" }));
        set("gender", "����");
        set("age", 25);
        set("long", "һ�����صĺ��ӣ��������޵����Ӿ��ˣ��������ܿ��ġ�\n");
         set("shen_type", 2);
        set_skill("dodge", 70);
    set("combat_exp", 100000000);
            set_skill("unarmed", 1000);
            set("force", 10000);
            set("max_qi", 1000000);
            set("qi", 1000000);
        set("jiali", 1500);   
       set("attitude","friendly");
      set("inquiry", ([
                "���" : (: ask_me :),
                "hongbao" : (: ask_me :),
                "liwu" : (: ask_me :),
                "����" : (: ask_me :),
        ]) );
        set("chat_msg", ({
             "�����޵�����˵����"+WHT+"��ӭ������������޵С�\n"NOR, 
             "��ӭ�������ǵ���Ϸ��",
             "��Ҫ�������������ҹ���<liwu>�����⣡",
             "ϣ�����ܳ�Ϊһ���콾��",
        }) );
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
    setup();
}
string ask_me()
{
        object ob;
        if ( (int)this_player()->query("hongbao_over") == 22 )
                return RANK_D->query_respect(this_player()) + 
                "���Ǹ���������?����ռ����ѽ��";
        if ( (int)this_player()->query("hongbao_over") == 1 )
                return RANK_D->query_respect(this_player()) + 
                "�㲻���Ѿ������������?����ռ����ѽ��";
        ob = new("/u/xgchen/hb.c");
        ob->move(this_player());
        this_player()->set("hongbao_over",22);
            message_vision("$N���һ�������ĺ����\n",this_player());

        return "ϣ����Ŭ����Ϊһ��������������";
}
