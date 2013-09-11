


#include <linux/string.h>
#include <linux/list.h>
#include <linux/gpio.h>
#include "config_mgr.h"
#include <hsad/config_general_struct.h>
#include "config_total_product.c"

#define NELEMENTS(ARRAY)    \
    (sizeof (ARRAY) / sizeof ((ARRAY)[0]))


/*current board id*/
int g_current_board_id = 0;

/*common array length*/
static int max_length = 0;

struct list_head active_board_id_general_struct_list;

/*get int board id*/
int get_board_id_int(unsigned int board_id0, unsigned int board_id1)
{
	return (unsigned int)(((board_id0<<4) | (board_id1)) & 0x000000FF);
}

/*setup.c call set_hw_config,init list*/
bool select_hw_config(unsigned int board_id0, unsigned int board_id1)
{
	int count = 0;
	int i = 0;
	config_pair *pconfig ;
	struct board_id_general_struct *config_pairs_ptr;
	
	/*get int board id store in global var:g_current_board_id*/
	g_current_board_id = get_board_id_int(board_id0, board_id1);
	HW_CONFIG_DEBUG("hsad: board_id0 is %u, boot_id1 is %u\n", board_id0, board_id1);
	
	INIT_LIST_HEAD(&active_board_id_general_struct_list);
	
	for(i = 0;i < NELEMENTS(hw_ver_total_configs ); i++) 
	{

			if(hw_ver_total_configs[i]->board_id==g_current_board_id){
				list_add(&(hw_ver_total_configs[i]->list), &active_board_id_general_struct_list);
				count++; 
			}				
	}
	
	/*common xml max length get*/
	config_pairs_ptr = get_board_id_general_struct(COMMON_MODULE_NAME);
	
	if(NULL == config_pairs_ptr)
	{
		HW_CONFIG_DEBUG(" can not find  module:common\n");
	}
	else
	{
	
		pconfig = (config_pair *)config_pairs_ptr->data_array.config_pair_ptr;
		while(NULL != pconfig->key)
		{
				pconfig++;
				max_length++;
		}
		
		#if 0
		//test xml
		
 		HW_CONFIG_DEBUG("GPIO163_USBSW_EN : %d\n",get_gpio_num_by_name("GPIO163_USBSW_EN"));
		HW_CONFIG_DEBUG("GPIO_USBSW_EN : %d\n",get_gpio_num_by_name("GPIO_USBSW_EN"));
		HW_CONFIG_DEBUG("GPIO122_LDO2V85_EN : %d\n",get_gpio_num_by_name("GPIO122_LDO2V85_EN"));
		HW_CONFIG_DEBUG("GPIO_LDO2V85_EN : %d\n",get_gpio_num_by_name("GPIO_LDO2V85_EN"));
		#endif
	
	
	}
	return (count!=0);
}

/*get module pointer*/
struct board_id_general_struct *get_board_id_general_struct(char * module_name)
{
	struct board_id_general_struct *p;
	struct list_head *pos;
	
	list_for_each(pos , &active_board_id_general_struct_list)
	{
		p = container_of(pos, struct board_id_general_struct,list);
		
		if(!strcmp(p->name, module_name))
			return p;
	}
	
	HW_CONFIG_DEBUG(" can not find  module:%s\n ", module_name);
	return NULL;
}

/*
  * Dependency: the array pointed by gp_active_configs should already sorted with keys, assending.
  * Description:   Binary Search the key.
  * Return Value: true for found, false for not found.
  * Parameters: key, the key want to be searched.
  *             pbuf, pointer for output buf.
  *             count, for output buf length.
  *             ptype, output the config data type.
  */
bool get_hw_config(const char* key, char* pbuf, size_t count,  unsigned int *ptype)
{
    /*need to get the length of config_pair array, for example, config_length*/
	int min = 0;
	int max  = max_length-1;
	struct board_id_general_struct *config_pairs_ptr;
	config_pair* pconfig = NULL;
	
	HW_CONFIG_DEBUG("hsad: getting config of key %s\n", key);

	config_pairs_ptr = get_board_id_general_struct(COMMON_MODULE_NAME);
	if(config_pairs_ptr)
		pconfig = (config_pair*)config_pairs_ptr->data_array.config_pair_ptr;
	else
		return false;
	if(0 == max_length){
		HW_CONFIG_DEBUG(" can not find  module:common\n");
		return false;
	}
   
    while(min <= max)
    {
        int result;
        int new_cursor = (min+max)/2;
        result = strcmp((pconfig+new_cursor)->key, key);
        if (0 == result)
        {
            /*found it, just return*/
	    if(pbuf)
	    {
		if ((pconfig+new_cursor)->type == E_CONFIG_DATA_TYPE_STRING)
		{
		    strncpy(pbuf, (char*)(pconfig+new_cursor)->data, count);
		}
		else
		{
		    unsigned int* pint = (unsigned int*)pbuf;
		    if (count < sizeof(unsigned int)) return false;
		    *pint = (pconfig+new_cursor)->data;
		}
	    }
            if(ptype) *ptype = (pconfig+new_cursor)->type;
	    if (E_CONFIG_DATA_TYPE_STRING == (pconfig+new_cursor)->type)
	    {
		HW_CONFIG_DEBUG("hsad: key-- %s, value: %s, type: string\n", (pconfig+new_cursor)->key,(char*)(pconfig+new_cursor)->data);
	    }
	    else
	    {
		HW_CONFIG_DEBUG("hsad: key-- %s, value: %u, type: %u\n", (pconfig+new_cursor)->key,(pconfig+new_cursor)->data, (pconfig+new_cursor)->type);
	    }
            return true;
        }
        else if (result > 0)
        {
            /* key is smaller, update max*/
            max = new_cursor-1;
        }
        else if (result < 0)
        {
            /* key is bigger, update min*/
            min = new_cursor+1;
        }        
    }

    /*Damn, not found!*/
    HW_CONFIG_DEBUG("hsad:get key %s failed.\n", key);

    return false;        
}
bool get_hw_config_string(const char* key, char* pbuf, size_t count, unsigned int* ptype)
{
    return get_hw_config(key, pbuf, count, ptype);
}

bool get_hw_config_int(const char* key, unsigned int* pint, unsigned int* ptype)
{
    return get_hw_config(key, (char*)pint, sizeof(unsigned int), ptype); 
}

bool get_hw_config_bool(const char* key, bool* pbool, unsigned int* ptype)
{
    int value;
    if(get_hw_config(key, (char*)&value, sizeof(int), ptype))
    {
        *pbool = (bool)value;
	return true;
    }
    return false;
}

bool get_hw_config_enum(const char* key, char* pbuf, size_t count, unsigned int* ptype)
{
    return get_hw_config(key, pbuf, count, ptype); 
}
