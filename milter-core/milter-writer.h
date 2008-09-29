/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) 2008  Kouhei Sutou <kou@cozmixng.org>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MILTER_WRITER_H__
#define __MILTER_WRITER_H__

#include <sys/types.h>
#include <sys/socket.h>

#include <glib-object.h>

#include <milter-core/milter-protocol.h>
#include <milter-core/milter-option.h>

G_BEGIN_DECLS

#define MILTER_WRITER_ERROR           (milter_writer_error_quark())

#define MILTER_TYPE_WRITER            (milter_writer_get_type())
#define MILTER_WRITER(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), MILTER_TYPE_WRITER, MilterWriter))
#define MILTER_WRITER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass), MILTER_TYPE_WRITER, MilterWriterClass))
#define MILTER_IS_WRITER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), MILTER_TYPE_WRITER))
#define MILTER_IS_WRITER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), MILTER_TYPE_WRITER))
#define MILTER_WRITER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), MILTER_TYPE_WRITER, MilterWriterClass))

typedef enum
{
    MILTER_WRITER_ERROR_NO_WRITE_FUNC,
    MILTER_WRITER_ERROR_NO_DATA
} MilterWriterError;

typedef struct _MilterWriter         MilterWriter;
typedef struct _MilterWriterClass    MilterWriterClass;

struct _MilterWriter
{
    GObject object;
};

struct _MilterWriterClass
{
    GObjectClass parent_class;
};

GQuark           milter_writer_error_quark    (void);

GType            milter_writer_get_type       (void) G_GNUC_CONST;

MilterWriter    *milter_writer_string_new     (GString          *string);
MilterWriter    *milter_writer_io_channel_new (GIOChannel       *channel);

gboolean         milter_writer_write          (MilterWriter     *writer,
                                               const gchar      *chunk,
                                               gsize             chunk_size,
                                               gsize            *written_size,
                                               GError          **error);

G_END_DECLS

#endif /* __MILTER_WRITER_H__ */

/*
vi:ts=4:nowrap:ai:expandtab:sw=4
*/
