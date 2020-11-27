// test
// clean_up.c
// by Annihilator@ES2
// Adapted for XKX by Xiang (12/15/95)
//Updated by Dumb (2015/3/20) 


int clean_up()
{
        object *inv, ob;
        int i, no_clean;
		
		ob = this_object();

        if (! clonep() && ob->query("no_clean_up") == 1) return 1;

        if (ob->query("no_clean_up") > 1)
                   log_file("no_clean_up", base_name(ob) + "flag ="
                            "= " + ob->query("no_clean_up") + "\n");

        if (interactive(ob)) return 1;
		

        if (ob->query_temp("quest_ob"))
                // ����ΪQUEST����
                return 1;

        // If we are contained in something, let environment do the clean
        // up instead of making recursive call. This will prevent clean-up
        // time lag.
		if (environment()) return 1;
				

        inv = all_inventory();
		no_clean = 0;
		
        for (i = 0; i < sizeof(inv); i++)
		{
			if (interactive(inv[i]) ||
			    inv[i]->is_character()||			
                inv[i]->query_temp("quest_ob") ||
                inv[i]->is_stay_in_room()) 
				{
					no_clean=1;
					continue;
				}	
				
			if (inv[i]->query("startroom") == base_name(ob) || !clonep(inv[i]))
				continue; 
				
			if (ob->query("short"))
			{
				if(inv[i]->query_temp("last_env")&&inv[i]->query_temp("last_env") == ob) 
				{
					inv[i]->add_temp("trash",1);
					if (inv[i]->query_temp("trash")>2) 
					{
						destruct(inv[i]);
						if (ob->query("outdoors"))
                                message("vision", "һ��紵����������һЩ������\n", ob);                                       
                        else
                                message("vision", "ͻȻ��������һ���������󣬺������˵�ʲô�Ƶġ�\n",ob);                                        
					}
				} else
				{
					inv[i]->set_temp("last_env",ob);
					inv[i]->delete_temp("trash");
				}
				
			}
		}
		
        if (no_clean == 1) return 1;    			 

        destruct(ob);
        if (objectp(ob))
                 log_file("no_destructed", base_name(ob) + " flag ="
                          "= " + ob->query("no_clean_up") + "\n");
 
        return 0;
}
