// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <memory>
#include <variant>

namespace parquet {

/// RowRanges is a collection of non-overlapping and ascendingly ordered row ranges.
class RowRanges {
 public:
  /// A range of contiguous rows represented by a start and end index.
  /// Both start and end are inclusive.
  struct IntervalRange {
    int64_t start;
    int64_t end;
  };

  /// A range of rows represented by a bitmap.
  struct BitmapRange {
    /// Start offset of the range.
    int64_t offset;
    /// Zero added if there are less than 64 elements left in the column.
    uint64_t bitmap;
  };

  /// An end marker for the row range iterator.
  struct End {};

  /// An iterator for accessing row ranges in order.
  class Iterator {
   public:
    virtual ~Iterator() = default;
    virtual std::variant<IntervalRange, BitmapRange, End> NextRange() = 0;
  };

  std::unique_ptr<Iterator> NewIterator();

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace parquet
