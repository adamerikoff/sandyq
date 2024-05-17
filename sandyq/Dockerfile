# Use the official Go image as base
FROM golang:1.22.1-alpine AS builder

# Set the working directory inside the container
WORKDIR /app

# Copy the Go modules manifests
COPY go.mod ./

# Download and install dependencies
RUN go mod download

# Copy the source code into the container
COPY . .

# Build the Go application
RUN CGO_ENABLED=0 GOOS=linux go build -o app .

# Use a minimal base image to reduce the size of the final image
FROM alpine:latest

# Set the working directory inside the container
WORKDIR /root/

# Copy the compiled binary from the builder stage
COPY --from=builder /app/app .

# Expose port 8080 to the outside world
EXPOSE 80

# Command to run the executable
CMD ["./app"]
