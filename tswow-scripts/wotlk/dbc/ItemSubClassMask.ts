/*
 * Copyright (C) 2020 tswow <https://github.com/tswow/>
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

/* tslint:disable */
import { int, loc_constructor } from '../../data/primitives'
import { Relation } from '../../data/query/Relations'
import { PrimaryKey } from '../../data/table/PrimaryKey'
import { DBCIntCell, DBCKeyCell, DBCLocCell } from '../../data/dbc/DBCCell'
import { DBCFile } from '../../data/dbc/DBCFile'
import { DBCRow } from '../../data/dbc/DBCRow'

 /**
  * Main row definition
  * - Add column comments to the commented getters below
  * - Add file comments to DBCFiles.ts
  */
export class ItemSubClassMaskRow extends DBCRow<ItemSubClassMaskCreator,ItemSubClassMaskQuery> {
    /**
     * Primary Key
     *
     * No comment (yet!)
     */
    @PrimaryKey()
    get ClassID() { return new DBCKeyCell(this,this.buffer,this.offset+0)}

    /**
     * No comment (yet!)
     */
    get flag() { return new DBCIntCell(this,this.buffer,this.offset+4)}

    /**
     * No comment (yet!)
     */
    get Name() { return new DBCLocCell(this,this.buffer,this.offset+8)}

    /**
     * Creates a clone of this row with new primary keys.
     *
     * Cloned rows are automatically added at the end of the DBC file.
     */
    clone(ClassID : int, c? : ItemSubClassMaskCreator) : this {
        return this.cloneInternal([ClassID],c);
    }
}

/**
 * Used for object creation (Don't comment these)
 */
export type ItemSubClassMaskCreator = {
    flag?: int
    Name?: loc_constructor
}

/**
 * Used for queries (Don't comment these)
 */
export type ItemSubClassMaskQuery = {
    ClassID? : Relation<int>
    flag? : Relation<int>
    Name? : Relation<string>
}

/**
 * Table definition (specifies arguments to 'add' function)
 * - Add file comments to DBCFiles.ts
 */
export class ItemSubClassMaskDBCFile extends DBCFile<
    ItemSubClassMaskCreator,
    ItemSubClassMaskQuery,
    ItemSubClassMaskRow> {
    constructor() {
        super('ItemSubClassMask',(t,b,o)=>new ItemSubClassMaskRow(t,b,o))
    }
    /** Loads a new ItemSubClassMask.dbc from a file. */
    static read(path: string): ItemSubClassMaskDBCFile {
        return new ItemSubClassMaskDBCFile().read(path);
    }
    add(ClassID : int, c? : ItemSubClassMaskCreator) : ItemSubClassMaskRow {
        return this.makeRow(0).clone(ClassID,c)
    }
}