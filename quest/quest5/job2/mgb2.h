void init()
{
        ::init();
        add_action("do_kill","kill");
        add_action("do_kill","hit");    
        add_action("do_kill","touxi");
        add_action("do_kill","teamkill");
        add_action("do_kill","fight");
        command("yun powerup");
        
        if (! this_object()->is_fighting())
                call_out("destruct_me", 2, this_object());
}

int do_kill(string arg)
{
        object who = this_player();
        object me = this_object();
        
        if (! arg || present(arg, environment(me)) != me) 
                return 0;
                
        if (me->query("ygjg") == who)
        {
                  message_vision(CYN "$N���ͣ�$N���ͣ�\n" NOR, who);
                  return 1;
        }
        else 
        if (me->query("ygjg"))
        {
                  tell_object(who, CYN "�㻹�Ǹ�˾��ְ��ר�ĶԸ����" HIR "�ɹű�" CYN "�ɡ�\n" NOR);
                  return 1;
        }
        return 0;
} 

void destruct_me(object ob)
{
        if (objectp(ob) && (ob->is_fighting() || ! living(ob)))
        {
                remove_call_out("destruct_me");
                call_out("destruct_me", 2, ob);
                return;
        }

        if (objectp(ob))
        {
                remove_call_out("destruct_me");
                destruct(ob);
        }
        return;
}

