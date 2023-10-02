#pragma once

class VertexBuffer {
        public:
        VertexBuffer(const void* data, size_t dataSize, unsigned int usage) // shouldnt be GLEnum
        : data_(data), dataSize_(dataSize), usage_(usage) {}

        const void* getData() const { return data_; }
        size_t getDataSize() const { return dataSize_; }
        unsigned int getUsage() const { return usage_; }

        private:
        const void* data_;
        size_t dataSize_;
        unsigned int usage_;
};