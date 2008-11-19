/* -*- c-file-style: "ruby" -*- */

#ifndef __RB_MILTER_MANAGER_PRIVATE_H__
#define __RB_MILTER_MANAGER_PRIVATE_H__

#include "rb-milter-manager.h"

extern void Init_milter_manager (void);
extern void Init_milter_manager_configuration (void);
extern void Init_milter_manager_child (void);
extern void Init_milter_manager_egg (void);
extern void Init_milter_manager_children (void);
extern void Init_milter_manager_control_command_encoder (void);
extern void Init_milter_manager_control_reply_encoder (void);
extern void Init_milter_manager_control_decoder (void);

#endif
